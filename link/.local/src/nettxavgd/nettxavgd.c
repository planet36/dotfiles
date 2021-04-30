// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <err.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

const char program_author[] = "Steven Ward";
const char program_version[] = "21w17a"; // date +'%yw%Ua'

const unsigned int default_init_delay_ms = 2000;
const unsigned int default_interval_ms = 2000;

FILE* dest_fp = NULL;
const char* dest_path = NULL;

volatile sig_atomic_t done = 0;
volatile sig_atomic_t reset_alarm = 1;

void
signal_handler(int signum)
{
	switch (signum)
	{
	case SIGALRM:
		// no op
		break;

	case SIGUSR1:
	case SIGUSR2:
		reset_alarm = 1;
		break;

	default:
		done = 1;
		break;
	}
}

void cleanup()
{
	if (dest_fp != NULL)
	{
		if (fclose(dest_fp) < 0)
		{
			perror("fclose");
		}
	}

	if (dest_path != NULL && done)
	{
		if (remove(dest_path) < 0)
		{
			perror("remove");
		}
	}
}

void print_version(const char* argv0)
{
	printf("%s %s\n", argv0, program_version);
	printf("Written by %s\n", program_author);
}

void print_usage(const char* argv0)
{
	printf("Usage: %s [OPTIONS] NETWORK_INTERFACE\n", argv0);
	printf("\n");
	printf("Continuously measure the average network transmit speed at a regular interval, and write the measurement to stdout or a temporary file.\n");
	printf("\n");
	printf("The unit of measurement of network speed is bytes/second.\n");
	printf("\n");
	printf("NETWORK_INTERFACE is a name found in /sys/class/net/.\n");
	printf("\n");

	printf("OPTIONS\n");
	printf("  -V       Print the version information and exit.\n");
	printf("  -h       Print this message and exit.\n");
	printf("  -f FILE  Specify the temporary output file.\n");
	printf("           FILE must not exist when this daemon starts.\n");
	printf("           FILE is truncated before every measurement is written.\n");
	printf("           FILE is removed when this daemon exits successfully.\n");
	printf("  -i MSEC  Specify the interval (in milliseconds) between measurements.\n");
	printf("           MSEC must be a positive integer.\n");
	printf("           The default value is %u.\n", default_interval_ms);
	printf("\n");
}

int main(int argc, char* const argv[])
{
	unsigned int init_delay_ms = default_init_delay_ms;
	unsigned int interval_ms = default_interval_ms;

	int oc;
	const char* short_options = "+:Vhf:i:";
	opterr = 0;
	while ((oc = getopt(argc, argv, short_options)) != -1)
	{
		switch (oc)
		{
		case 'V':
			print_version(argv[0]);
			return EXIT_SUCCESS;

		case 'h':
			print_usage(argv[0]);
			return EXIT_SUCCESS;

		case 'f':
			dest_path = optarg;
			break;

		case 'i':
			interval_ms = strtou(optarg);
			if (interval_ms == 0)
			{
				errx(EXIT_FAILURE, "invalid interval: %u", interval_ms);
			}
			// There is no option for specifying the initial delay.
			init_delay_ms = interval_ms;
			break;

		case '?':
			errx(EXIT_FAILURE, "unknown option: '%s'", escape_char(optopt));
			break;

		case ':':
			errx(EXIT_FAILURE, "option requires a value: '%s'", escape_char(optopt));
			break;

		default:
			errx(EXIT_FAILURE, "unhandled option: '%s'", escape_char(oc));
			break;
		}
	}

	if (optind >= argc)
	{
		errx(EXIT_FAILURE, "missing NETWORK_INTERFACE operand");
	}

	// {{{ adapted from my slstatus
	// https://github.com/planet36/slstatus/blob/master/components/netspeeds.c
	char net_interface_path[PATH_MAX] = {'\0'};
	int n = snprintf(net_interface_path, sizeof (net_interface_path),
	                 "/sys/class/net/%s/statistics/tx_bytes", argv[optind]);

	if (n < 0 || (size_t)n >= sizeof (net_interface_path))
	{
		errx(EXIT_FAILURE, "snprintf");
		return -1;
	}
	// }}}

	atexit(cleanup);

	if (dest_path != NULL)
	{
		const mode_t new_mask = 0133; // rw-r--r--
		(void)umask(new_mask);

		if ((dest_fp = fopen(dest_path, "wx")) == NULL)
		{
			err(EXIT_FAILURE, "%s", dest_path);
		}

		if (fclose(dest_fp) < 0)
		{
			dest_fp = NULL;
			err(EXIT_FAILURE, "fclose");
		}
		dest_fp = NULL;
	}

	struct sigaction signal_action;
	(void)memset(&signal_action, 0, sizeof (signal_action));
	signal_action.sa_flags = SA_RESTART;
	signal_action.sa_handler = signal_handler;

	if (sigfillset(&signal_action.sa_mask) < 0)
	{
		err(EXIT_FAILURE, "sigfillset");
	}

	const int signals_to_handle[] = {
		SIGALRM,
		SIGHUP,
		SIGINT,
		SIGPIPE,
		SIGQUIT,
		SIGTERM,
		SIGUSR1,
		SIGUSR2,
	};

	for (size_t i = 0; i < sizeof (signals_to_handle) / sizeof (signals_to_handle[0]); ++i)
	{
		if (sigaction(signals_to_handle[i], &signal_action, NULL) < 0)
		{
			err(EXIT_FAILURE, "sigaction");
		}
	}

	sigset_t empty_mask;
	if (sigemptyset(&empty_mask) < 0)
	{
		err(EXIT_FAILURE, "sigemptyset");
	}

	sigset_t full_mask;
	if (sigfillset(&full_mask) < 0)
	{
		err(EXIT_FAILURE, "sigfillset");
	}

	sigset_t orig_mask;
	// block everything and save current signal mask
	if (sigprocmask(SIG_BLOCK, &full_mask, &orig_mask) < 0)
	{
		err(EXIT_FAILURE, "sigprocmask");
	}

	const struct timeval init_delay = milliseconds_to_timeval(init_delay_ms);
	const struct timeval interval = milliseconds_to_timeval(interval_ms);

	const struct itimerval itv = {
		.it_interval = interval,
		.it_value = init_delay, // If zero, the alarm is disabled.
	};

	bool first_iteration = true;
	double prev_now_s = 0;
	uintmax_t prev_txbytes = 0;

	do
	{
		if (reset_alarm)
		{
			if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
			{
				err(EXIT_FAILURE, "setitimer");
			}
			reset_alarm = 0;
		}

		struct timespec now_ts;

		if (clock_gettime(CLOCK_MONOTONIC, &now_ts) < 0)
		{
			err(EXIT_FAILURE, "clock_gettime");
		}

		const double now_s = timespec_to_double(&now_ts);

		uintmax_t txbytes = 0;

		if (pscanf(net_interface_path, "%ju", &txbytes) != 1)
		{
			errx(EXIT_FAILURE, "error scanning '%s'", net_interface_path);
		}

		if (first_iteration)
		{
			first_iteration = 0;
		}
		else
		{
			const double delta_time_s = now_s - prev_now_s;

			uintmax_t txbytes_per_s = 0;

			if (delta_time_s != 0)
			{
				// round to nearest int
				txbytes_per_s = (uintmax_t)(((txbytes - prev_txbytes) / delta_time_s) + 0.5);
			}

			char dest_buf[32] = {'\0'};
			(void)snprintf(dest_buf, sizeof (dest_buf), "%ju", txbytes_per_s);

			if (dest_path != NULL)
			{
				if ((dest_fp = fopen(dest_path, "w")) == NULL)
				{
					err(EXIT_FAILURE, "%s", dest_path);
				}

				if (fputs(dest_buf, dest_fp) < 0)
				{
					err(EXIT_FAILURE, "fputs");
				}

				if (fclose(dest_fp) < 0)
				{
					dest_fp = NULL;
					err(EXIT_FAILURE, "fclose");
				}
				dest_fp = NULL;
			}
			else
			{
				if (puts(dest_buf) < 0)
				{
					err(EXIT_FAILURE, "puts");
				}
			}
		}

		prev_now_s = now_s;
		prev_txbytes = txbytes;

		if (!done)
		{
			(void)sigsuspend(&empty_mask);
		}

	} while (!done);

	if (sigprocmask(SIG_SETMASK, &orig_mask, NULL) < 0)
	{
		err(EXIT_FAILURE, "sigprocmask");
	}

	return EXIT_SUCCESS;
}
