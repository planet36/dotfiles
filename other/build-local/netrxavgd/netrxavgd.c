// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "acfile.h"
#include "pscanf.h"
#include "strtou.h"
#include "timespec.h"
#include "timeval.h"

#include <assert.h>
#include <dirent.h>
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

int
scandir_filter(const struct dirent* dirent)
{
    // Exclude these names
    return strcmp(dirent->d_name, ".") != 0 &&
           strcmp(dirent->d_name, "..") != 0 &&
           strcmp(dirent->d_name, "lo") != 0;
}

const char* program_author = "Steven Ward";
const char* program_version = "1.2.2";
const char* program_license = "OSL-3.0";

constexpr unsigned int default_init_delay_msec = 2000;
constexpr unsigned int default_interval_msec = 2000;
char default_net_iface[NAME_MAX + 1] = {'\0'};

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
set_default_net_iface()
{
    struct dirent** namelist;
    int n;

    n = scandir("/sys/class/net/", &namelist, scandir_filter, alphasort);
    if (n == -1)
        err(EXIT_FAILURE, "scandir");

    (void)strncpy(default_net_iface, namelist[0]->d_name, sizeof(default_net_iface));
    default_net_iface[sizeof(default_net_iface) - 1] = '\0';

    while (n--)
    {
        free(namelist[n]);
    }
    free(namelist);
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
    printf("Usage: %s [OPTION]...\n", program_invocation_short_name);
    printf("\n");
    printf("Continuously measure the average network receive speed at a regular interval, and write the measurement to stdout or a temporary file.\n");
    printf("\n");
    printf("The unit of measurement of network speed is bytes/second.\n");
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
    printf("  -n NET   Specify the network interface.\n");
    printf("           NET is a name found in /sys/class/net/.\n");
    printf("           The default value is \"%s\".\n", default_net_iface);
    printf("\n");
}

int
main(int argc, char* const argv[])
{
    set_default_net_iface();
    unsigned int init_delay_msec = default_init_delay_msec;
    unsigned int interval_msec = default_interval_msec;
    char* net_iface = default_net_iface;

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

        case 'n':
            net_iface = optarg;
            break;

        default:
            exit(EXIT_FAILURE);
        }
    }

    // {{{ Adapted from my slstatus
    // https://github.com/planet36/slstatus/blob/main/components/netspeeds.c
    char net_iface_path[PATH_MAX] = {'\0'};
    int n = snprintf(net_iface_path, sizeof(net_iface_path),
                     "/sys/class/net/%s/statistics/rx_bytes", net_iface);

    if (n < 0 || (size_t)n >= sizeof(net_iface_path))
    {
        errx(EXIT_FAILURE, "snprintf");
        return -1;
    }
    // }}}

    // Test if file is readable
    {
        ACFILEPTR fp = fopen(net_iface_path, "r");
        if (fp == NULL)
            err(EXIT_FAILURE, "%s", net_iface_path);
    }

    assert(atexit(atexit_cleanup) == 0);

    if (dest_path != NULL)
    {
        constexpr mode_t new_mask = 0133; // rw-r--r--
        (void)umask(new_mask);

        ACFILEPTR dest_fp = fopen(dest_path, "wx");
        if (dest_fp == NULL)
            err(EXIT_FAILURE, "%s", dest_path);
    }

    struct sigaction signal_action;
    (void)memset(&signal_action, 0, sizeof(signal_action));
    signal_action.sa_flags = SA_RESTART;
    signal_action.sa_handler = signal_handler;

    if (sigfillset(&signal_action.sa_mask) < 0)
        err(EXIT_FAILURE, "sigfillset");

    constexpr int signals_to_handle[] = {
        SIGALRM,
        SIGHUP,
        SIGINT,
        SIGPIPE,
        SIGQUIT,
        SIGTERM,
        SIGUSR1,
        SIGUSR2,
    };

    constexpr size_t num_signals_to_handle =
        sizeof(signals_to_handle) / sizeof(signals_to_handle[0]);
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
    double prev_now_s = 0;
    uintmax_t prev_rx_bytes = 0;

    do
    {
        if (reset_alarm)
        {
            if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
                err(EXIT_FAILURE, "setitimer");
            reset_alarm = 0;
        }

        struct timespec now_ts;

        if (clock_gettime(CLOCK_MONOTONIC, &now_ts) < 0)
            err(EXIT_FAILURE, "clock_gettime");

        const double now_s = timespec_to_sec(&now_ts);

        uintmax_t rx_bytes = 0;

        if (pscanf(net_iface_path, "%ju", &rx_bytes) != 1)
            errx(EXIT_FAILURE, "error scanning '%s'", net_iface_path);

        if (first_iteration)
            first_iteration = false;
        else
        {
            const double delta_time_s = now_s - prev_now_s;

            uintmax_t rx_bytes_per_s = 0;

            if (delta_time_s != 0)
                // round to nearest int
                rx_bytes_per_s = (uintmax_t)(
                                     (double)(rx_bytes - prev_rx_bytes) / delta_time_s + 0.5
                                 );

            char dest_buf[32] = {'\0'};
            (void)snprintf(dest_buf, sizeof(dest_buf), "%ju", rx_bytes_per_s);

            if (dest_path != NULL)
            {
                ACFILEPTR dest_fp = fopen(dest_path, "w");
                if (dest_fp == NULL)
                    err(EXIT_FAILURE, "%s", dest_path);

                if (fputs(dest_buf, dest_fp) < 0)
                    err(EXIT_FAILURE, "fputs");
            }
            else if (puts(dest_buf) < 0)
                err(EXIT_FAILURE, "puts");
        }

        prev_now_s = now_s;
        prev_rx_bytes = rx_bytes;

        if (!done)
            (void)sigsuspend(&empty_mask);
    }
    while (!done);

    if (sigprocmask(SIG_SETMASK, &orig_mask, NULL) < 0)
        err(EXIT_FAILURE, "sigprocmask");

    return EXIT_SUCCESS;
}
