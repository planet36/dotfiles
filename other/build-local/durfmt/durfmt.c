// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char program_author[] = "Steven Ward";
const char program_version[] = "1.0.1";

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

const char ut_abbr[UT_MAX] = {
	[UT_SECOND] = 's',
	[UT_MINUTE] = 'm',
	[UT_HOUR  ] = 'h',
	[UT_DAY   ] = 'd',
	[UT_WEEK  ] = 'w',
	[UT_YEAR  ] = 'y',
};

bool valid_ut_abbr(const char c)
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

enum UT ut_from_c(const char c)
{
	enum UT ut = -1;

	switch (tolower(c))
	{
	case 's': ut = UT_SECOND; break;
	case 'm': ut = UT_MINUTE; break;
	case 'h': ut = UT_HOUR  ; break;
	case 'd': ut = UT_DAY   ; break;
	case 'w': ut = UT_WEEK  ; break;
	case 'y': ut = UT_YEAR  ; break;
	default: break;
	}

	return ut;
}

const unsigned long seconds_per[UT_MAX] = {
	[UT_SECOND] =        1UL,
	[UT_MINUTE] =       60UL,
	[UT_HOUR  ] =     3600UL, // 60*60
	[UT_DAY   ] =    86400UL, // 60*60*24
	[UT_WEEK  ] =   604800UL, // 60*60*24*7
	[UT_YEAR  ] = 31556952UL, // 60*60*24*365.2425
};

struct durfmt_opts
{
	int width[UT_MAX];
	bool print[UT_MAX];
	bool print_inter_zero_values;
	bool print_all_zero_values;
	bool suppress_newline;
};

void durfmt_opts_init(struct durfmt_opts* opts)
{
	for (enum UT ut = UT_SECOND; ut <= UT_YEAR; ++ut)
	{
		opts->width[ut] = 1;
		opts->print[ut] = false;
	}

	opts->print_inter_zero_values = false;
	opts->print_all_zero_values = false;
	opts->suppress_newline = false;
}

void durfmt(unsigned long duration, const struct durfmt_opts* opts)
{
	enum UT last_ut = -1;
	unsigned long vals[UT_MAX] = {0};
	bool printed_something = false;

	for (enum UT ut = UT_SECOND; ut <= UT_YEAR; ++ut)
	{
		if (opts->print[ut])
		{
			last_ut = ut;
			break;
		}
	}

	// the controlling expression must consider unsigned integer wrap around
	for (enum UT ut = UT_YEAR; ut >= UT_SECOND && ut <= UT_YEAR; --ut)
	{
		if (opts->print[ut])
		{
			vals[ut] = duration / seconds_per[ut];
			duration = duration % seconds_per[ut];

			if (vals[ut] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == ut) && opts->print_inter_zero_values))
			{
				if (printed_something)
					putchar(' ');
				printf("%0*lu", opts->width[ut], vals[ut]);
				putchar(ut_abbr[ut]);
				printed_something = true;
			}
		}
	}

	if (printed_something && !opts->suppress_newline)
		putchar('\n');
}

void print_version(const char* argv0)
{
	printf("%s %s\n", argv0, program_version);
	printf("Written by %s\n", program_author);
}

void print_usage(const char* argv0)
{
	printf("Usage: %s [OPTIONS]\n", argv0);
	printf("\n");
	printf("Read a non-negative duration (in seconds) from stdin.\n");
	printf("Break down the duration into whole numbers of\n");
	printf("  years, weeks, days, hours, minutes, and seconds.\n");
	printf("Values of zero are not printed by default.\n");
	printf("\n");

	printf("OPTIONS\n");
	printf("  -V        Print the version information and exit.\n");
	printf("  -h        Print this message and exit.\n");
	printf("  -n        Do not print a trailing newline character.\n");
	printf("  -p UNITS  Specify the units of time to be printed.  Omitted units of time are not printed.\n");
	printf("            If this option is given more than once, only the last occurrence is respected.\n");
	printf("            The default value is 'ywdhms'.\n");
	printf("  -w WIDTH  Specify the minimum field width for hours, minutes, and seconds values.\n");
	printf("            If the value of the field has fewer digits than WIDTH, it will be padded with zeros on the left.\n");
	printf("            WIDTH must be a non-negative integer.\n");
	printf("            The default value is 1.\n");
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

void print_option_err(const char* argv0, const char* msg, const int o)
{
	if (isprint(o))
		fprintf(stderr, "%s: %s: '%c'\n", argv0, msg, o);
	else
		fprintf(stderr, "%s: %s: '\\x%x'\n", argv0, msg, o);
}

int main(int argc, char* argv[])
{
	struct durfmt_opts opts;
	const char* ut_to_print = "ywdhms";

	durfmt_opts_init(&opts);

	int oc;
	const char* short_options = "+:Vhnp:w:0";
	opterr = 0;
	while ((oc = getopt(argc, argv, short_options)) != -1)
	{
		switch (oc)
		{
		case 'V':
			print_version(argv[0]);
			return 0;

		case 'h':
			print_usage(argv[0]);
			return 0;

		case 'n':
			opts.suppress_newline = true;
			break;

		case 'p':
			ut_to_print = optarg;
			break;

		case 'w':
			long width = strtol(optarg, NULL, 0);
			if (width < 0) width = 0;
			else if (width > 20) width = 20;
			opts.width[UT_SECOND] = opts.width[UT_MINUTE] = opts.width[UT_HOUR] = (int)width;
			break;

		case '0':
			opts.print_all_zero_values = opts.print_inter_zero_values;
			opts.print_inter_zero_values = true;
			break;

		case '?':
			print_option_err(argv[0], "Unknown option", optopt);
			return 1;

		case ':':
			print_option_err(argv[0], "Option requires a value", optopt);
			return 1;

		default:
			return 1;
		}
	}

	//argc -= optind;
	//argv += optind;

	for (size_t i = 0; ut_to_print[i]; ++i)
	{
		if (!valid_ut_abbr(ut_to_print[i]))
		{
			print_option_err(argv[0], "Invalid option value", ut_to_print[i]);
			return 1;
		}

		opts.print[ut_from_c(ut_to_print[i])] = true;
	}

	char* line = NULL;
	size_t n = 0;
	//ssize_t bytes_read = 0;
	//while ((bytes_read = getline(&line, &n, stdin)) != EOF)
	while (getline(&line, &n, stdin) != EOF)
	{
		unsigned long seconds = strtoul(line, NULL, 0);
		durfmt(seconds, &opts);
		free(line);
		line = NULL;
		n = 0;
	}

	return 0;
}
