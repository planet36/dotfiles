// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
// automatically close file stream
#define ACFILE(varname) \
	__attribute__((cleanup(cleanup_close_file))) FILE* varname = NULL

unsigned int
strtou(const char* s)
{
	unsigned long i = strtoul(s, NULL, 0);
	if (i > UINT_MAX)
		i = UINT_MAX;
	return (unsigned int)i;
}

void
cleanup_close_file(FILE** fpp)
{
	if (*fpp != NULL)
	{
		if (fclose(*fpp) < 0)
		{
			*fpp = NULL;
			err(EXIT_FAILURE, "fclose");
		}
		*fpp = NULL;
	}
}

// {{{ copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/util.c

int
pscanf(const char* path, const char* fmt, ...)
{
	FILE* fp;
	va_list ap;
	int n;

	fp = fopen(path, "r");
	if (fp == NULL)
	{
		warn("fopen '%s'", path);
		return -1;
	}
	va_start(ap, fmt);
	n = vfscanf(fp, fmt, ap);
	va_end(ap);
	if (fclose(fp) < 0)
	{
		err(EXIT_FAILURE, "fclose");
	}

	return (n == EOF) ? -1 : n;
}

double
timespec_to_sec(const struct timespec* ts)
{
	return (double)ts->tv_sec + copysign((double)ts->tv_nsec, (double)ts->tv_sec) / 1E9;
}

struct timeval
msec_to_timeval(unsigned int msec)
{
	return (struct timeval){
	    .tv_sec = msec / 1000U,
	    .tv_usec = (msec % 1000U) * 1000UL,
	};
}

// }}}

// {{{ copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/components/cpu.c

int
calc_idle(uintmax_t* idle, uintmax_t* sum)
{
	uintmax_t a[6];

	// cpu user nice system idle iowait irq softirq
	if (pscanf("/proc/stat", "%*s %ju %ju %ju %ju %*s %ju %ju",
	           &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]) != 6)
	{
		return -1;
	}

	*idle = a[3];
	*sum = a[0] + a[1] + a[2] + a[3] + a[4] + a[5];

	return 0;
}

// }}}

const char* program_author = "Steven Ward";
const char* program_version = "1.1.2";
const char* program_license = "OSL-3.0";

const unsigned int default_init_delay_msec = 2000;
const unsigned int default_interval_msec = 2000;

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

void
atexit_cleanup()
{
	if (dest_path != NULL && done)
		if (remove(dest_path) < 0)
			perror("remove");
}

void
print_version()
{
	printf("%s %s\n", program_invocation_short_name, program_version);
	printf("License: %s\n", program_license);
	printf("Written by %s\n", program_author);
}

void
print_usage()
{
	printf("Usage: %s [OPTIONS]\n", program_invocation_short_name);
	printf("\n");
	printf("Continuously measure the average CPU usage at a regular interval, and write the measurement to stdout or a temporary file.\n");
	printf("\n");
	printf("CPU usage is a real number within the interval [0, 1].\n");
	printf("\n");

	printf("OPTIONS\n");
	printf("  -V       Print the version information, then exit.\n");
	printf("\n");
	printf("  -h       Print this message, then exit.\n");
	printf("\n");
	printf("  -f FILE  Specify the temporary output file.\n");
	printf("           FILE must not exist when this daemon starts.\n");
	printf("           FILE is truncated before every measurement is written.\n");
	printf("           FILE is removed when this daemon exits successfully.\n");
	printf("\n");
	printf("  -i MSEC  Specify the interval (in milliseconds) between measurements.\n");
	printf("           MSEC must be a positive integer.\n");
	printf("           The default value is %u.\n", default_interval_msec);
	printf("\n");
}

int main(int argc, char* const argv[])
{
	unsigned int init_delay_msec = default_init_delay_msec;
	unsigned int interval_msec = default_interval_msec;

	int oc;
	const char* short_options = "+:Vhf:i:";
	while ((oc = getopt(argc, argv, short_options)) != -1)
	{
		switch (oc)
		{
		case 'V':
			print_version();
			return EXIT_SUCCESS;

		case 'h':
			print_usage();
			return EXIT_SUCCESS;

		case 'f':
			dest_path = optarg;
			break;

		case 'i':
			interval_msec = strtou(optarg);
			if (interval_msec == 0)
				errx(EXIT_FAILURE, "invalid interval: %u", interval_msec);

			// There is no option for specifying the initial delay.
			init_delay_msec = interval_msec;
			break;

		default:
			exit(EXIT_FAILURE);
		}
	}

	assert(atexit(atexit_cleanup) == 0);

	if (dest_path != NULL)
	{
		const mode_t new_mask = 0133; // rw-r--r--
		(void)umask(new_mask);

		ACFILE(dest_fp);

		dest_fp = fopen(dest_path, "wx");
		if (dest_fp == NULL)
			err(EXIT_FAILURE, "%s", dest_path);
	}

	struct sigaction signal_action;
	(void)memset(&signal_action, 0, sizeof(signal_action));
	signal_action.sa_flags = SA_RESTART;
	signal_action.sa_handler = signal_handler;

	if (sigfillset(&signal_action.sa_mask) < 0)
		err(EXIT_FAILURE, "sigfillset");

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

	const size_t num_signals_to_handle = sizeof(signals_to_handle) /
	                                     sizeof(signals_to_handle[0]);
	for (size_t i = 0; i < num_signals_to_handle; ++i)
	{
		if (sigaction(signals_to_handle[i], &signal_action, NULL) < 0)
			err(EXIT_FAILURE, "sigaction");
	}

	sigset_t empty_mask;
	if (sigemptyset(&empty_mask) < 0)
		err(EXIT_FAILURE, "sigemptyset");

	sigset_t full_mask;
	if (sigfillset(&full_mask) < 0)
		err(EXIT_FAILURE, "sigfillset");

	sigset_t orig_mask;
	// block everything and save current signal mask
	if (sigprocmask(SIG_BLOCK, &full_mask, &orig_mask) < 0)
		err(EXIT_FAILURE, "sigprocmask");

	const struct timeval init_delay = msec_to_timeval(init_delay_msec);
	const struct timeval interval = msec_to_timeval(interval_msec);

	const struct itimerval itv = {
	    .it_interval = interval,
	    .it_value = init_delay, // If zero, the alarm is disabled.
	};

	bool first_iteration = true;
	uintmax_t prev_idle_ticks = 0;
	uintmax_t prev_sum_ticks = 0;

	do
	{
		if (reset_alarm)
		{
			if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
				err(EXIT_FAILURE, "setitimer");
			reset_alarm = 0;
		}

		uintmax_t idle_ticks = 0;
		uintmax_t sum_ticks = 0;

		if (calc_idle(&idle_ticks, &sum_ticks) < 0)
			errx(EXIT_FAILURE, "error scanning /proc/stat");

		if (first_iteration)
			first_iteration = false;
		else
		{
			double cpu_usage = 0;

			if (sum_ticks - prev_sum_ticks != 0)
				cpu_usage = 1 - (double)(idle_ticks - prev_idle_ticks) /
				                (double)(sum_ticks - prev_sum_ticks);

			char dest_buf[32] = {'\0'};
			(void)snprintf(dest_buf, sizeof(dest_buf), "%.6f", cpu_usage);

			if (dest_path != NULL)
			{
				ACFILE(dest_fp);

				dest_fp = fopen(dest_path, "w");
				if (dest_fp == NULL)
					err(EXIT_FAILURE, "%s", dest_path);

				if (fputs(dest_buf, dest_fp) < 0)
					err(EXIT_FAILURE, "fputs");
			}
			else if (puts(dest_buf) < 0)
				err(EXIT_FAILURE, "puts");
		}

		prev_idle_ticks = idle_ticks;
		prev_sum_ticks = sum_ticks;

		if (!done)
			(void)sigsuspend(&empty_mask);
	}
	while (!done);

	if (sigprocmask(SIG_SETMASK, &orig_mask, NULL) < 0)
		err(EXIT_FAILURE, "sigprocmask");

	return EXIT_SUCCESS;
}
