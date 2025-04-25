// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char* program_author = "Steven Ward";
const char* program_version = "1.0.2";
const char* program_license = "OSL-3.0";

constexpr int default_width = 1;
constexpr int max_width = 20;
const char* default_ut_to_print = "ywdhms";

/// unit of time
enum UT
{
    UT_SECOND,
    UT_MINUTE,
    UT_HOUR  ,
    UT_DAY   ,
    UT_WEEK  ,
    UT_YEAR  ,
    UT_MAX   , // must be last
};

constexpr char ut_abbr[UT_MAX] = {
    [UT_SECOND] = 's',
    [UT_MINUTE] = 'm',
    [UT_HOUR  ] = 'h',
    [UT_DAY   ] = 'd',
    [UT_WEEK  ] = 'w',
    [UT_YEAR  ] = 'y',
};

bool
valid_ut_abbr(const char c)
{
    switch (tolower(c))
    {
    case 's':
    case 'm':
    case 'h':
    case 'd':
    case 'w':
    case 'y':
        return true;
    default:
        return false;
    }
}

enum UT
ut_from_c(const char c)
{
    switch (tolower(c))
    {
    case 's': return UT_SECOND;
    case 'm': return UT_MINUTE;
    case 'h': return UT_HOUR  ;
    case 'd': return UT_DAY   ;
    case 'w': return UT_WEEK  ;
    case 'y': return UT_YEAR  ;
    default: unreachable();
    }
}

constexpr unsigned long seconds_per[UT_MAX] = {
    [UT_SECOND] =          1UL,
    [UT_MINUTE] =         60UL,
    [UT_HOUR  ] =      3'600UL, // 60*60
    [UT_DAY   ] =     86'400UL, // 60*60*24
    [UT_WEEK  ] =    604'800UL, // 60*60*24*7
    [UT_YEAR  ] = 31'556'952UL, // 60*60*24*365.2425
};

struct durfmt_opts
{
    int width[UT_MAX];
    bool print[UT_MAX];
    bool print_inter_zero_values;
    bool print_all_zero_values;
    bool suppress_newline;
};

void
durfmt_opts_init(struct durfmt_opts* opts)
{
    for (enum UT ut = UT_SECOND; ut <= UT_YEAR; ++ut)
    {
        opts->width[ut] = default_width;
        opts->print[ut] = false;
    }

    opts->print_inter_zero_values = false;
    opts->print_all_zero_values = false;
    opts->suppress_newline = false;
}

void
durfmt(unsigned long dur_secs, const struct durfmt_opts* opts)
{
    enum UT last_ut;
    bool printed_something = false;

    // Find the least significant unit of time to print.
    if (opts->print[UT_YEAR  ]) last_ut = UT_YEAR  ;
    if (opts->print[UT_WEEK  ]) last_ut = UT_WEEK  ;
    if (opts->print[UT_DAY   ]) last_ut = UT_DAY   ;
    if (opts->print[UT_HOUR  ]) last_ut = UT_HOUR  ;
    if (opts->print[UT_MINUTE]) last_ut = UT_MINUTE;
    if (opts->print[UT_SECOND]) last_ut = UT_SECOND;

    // the controlling expression must consider unsigned integer wrap around
    for (enum UT ut = UT_YEAR; ut >= UT_SECOND && ut <= UT_YEAR; --ut)
    {
        if (opts->print[ut])
        {
            unsigned long dur_ut = 0;
            dur_ut = dur_secs / seconds_per[ut];
            dur_secs = dur_secs % seconds_per[ut];

            if (dur_ut > 0 || opts->print_all_zero_values ||
                ((printed_something || last_ut == ut) &&
                 opts->print_inter_zero_values))
            {
                if (printed_something)
                    putchar(' ');
                printf("%0*lu", opts->width[ut], dur_ut);
                putchar(ut_abbr[ut]);
                printed_something = true;
            }
        }
    }

    if (printed_something && !opts->suppress_newline)
        putchar('\n');
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
    printf("Read a non-negative duration (in seconds) from stdin.\n");
    printf("Break down the duration into whole numbers of\n");
    printf("  years, weeks, days, hours, minutes, and seconds.\n");
    printf("Values of zero are not printed by default.\n");
    printf("\n");

    printf("OPTIONS\n");
    printf("  -V        Print the version information, then exit.\n");
    printf("  -h        Print this message, then exit.\n");
    printf("  -n        Do not print a trailing newline character.\n");
    printf("  -p UNITS  Specify the units of time to be printed.  Omitted units of time are not printed.\n");
    printf("            If this option is given more than once, only the last occurrence is respected.\n");
    printf("            At least one unit of time must be given.\n");
    printf("            The default value is '%s'.\n", default_ut_to_print);
    printf("  -w WIDTH  Specify the minimum field width for hours, minutes, and seconds values.\n");
    printf("            If the value of the field has fewer digits than WIDTH, it will be padded with zeros on the left.\n");
    printf("            WIDTH must be a non-negative integer.\n");
    printf("            The default value is %d.\n", default_width);
    printf("  -0        Print values of zero.\n");
    printf("            One -0 prints values of zero occurring after the most significant non-zero value.\n");
    printf("            Two -0 prints values of zero for all units of time.\n");
    printf("\n");

    printf("UNIT is a character representing one of the following units of time.\n");
    printf("  y = years\n");
    printf("  w = weeks\n");
    printf("  d = days\n");
    printf("  h = hours\n");
    printf("  m = minutes\n");
    printf("  s = seconds\n");
    printf("\n");
}

int
main(int argc, char* argv[])
{
    struct durfmt_opts opts;
    const char* ut_to_print = default_ut_to_print;

    durfmt_opts_init(&opts);

    int oc;
    const char* short_options = "+:Vhnp:w:0";
    long width = 0;
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

        case 'n':
            opts.suppress_newline = true;
            break;

        case 'p':
            ut_to_print = optarg;
            break;

        case 'w':
            width = strtol(optarg, NULL, 0);
            if (width < 0)
                width = 0;
            else if (width > max_width)
                width = max_width;
            opts.width[UT_SECOND] = opts.width[UT_MINUTE] =
                opts.width[UT_HOUR] = (int)width;
            break;

        case '0':
            opts.print_all_zero_values = opts.print_inter_zero_values;
            opts.print_inter_zero_values = true;
            break;

        default:
            exit(EXIT_FAILURE);
        }
    }

    //argc -= optind;
    //argv += optind;

    for (size_t i = 0; ut_to_print[i]; ++i)
    {
        if (!valid_ut_abbr(ut_to_print[i]))
        {
            errx(EXIT_FAILURE, "invalid unit of time: '%c'", ut_to_print[i]);
        }

        opts.print[ut_from_c(ut_to_print[i])] = true;
    }

    if (!opts.print[UT_SECOND] &&
        !opts.print[UT_MINUTE] &&
        !opts.print[UT_HOUR  ] &&
        !opts.print[UT_DAY   ] &&
        !opts.print[UT_WEEK  ] &&
        !opts.print[UT_YEAR  ])
    {
        errx(EXIT_FAILURE, "must specify at least one unit of time to be printed");
    }

    char* line = NULL;
    size_t allocated_size = 0;
    ssize_t bytes_read = 0;
    while ((bytes_read = getline(&line, &allocated_size, stdin)) != EOF)
    //while (getline(&line, &allocated_size, stdin) != EOF)
    {
        unsigned long dur_secs = strtoul(line, NULL, 0);
        durfmt(dur_secs, &opts);
    }
    free(line);
    line = NULL;
    allocated_size = 0;

    return EXIT_SUCCESS;
}
