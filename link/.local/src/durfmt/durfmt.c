// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char program_author[] = "Steven Ward";
const char program_version[] = "21w16a"; // date +'%yw%Ua'

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

int strtoi(const char* s)
{
	long i = strtol(s, NULL, 0);

	if (i < INT_MIN) i = INT_MIN;
	else if (i > INT_MAX) i = INT_MAX;

	return (int)i;
}

void my_div_i(
		const unsigned long x, const unsigned long y,
		unsigned long* quo, unsigned long* rem)
{
	*quo = (x / y);
	*rem = (x % y);
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
	opts->width[UT_SECOND] = 1;
	opts->width[UT_MINUTE] = 1;
	opts->width[UT_HOUR  ] = 1;
	opts->width[UT_DAY   ] = 1;
	opts->width[UT_WEEK  ] = 1;
	opts->width[UT_YEAR  ] = 1;

	opts->print[UT_SECOND] = false;
	opts->print[UT_MINUTE] = false;
	opts->print[UT_HOUR  ] = false;
	opts->print[UT_DAY   ] = false;
	opts->print[UT_WEEK  ] = false;
	opts->print[UT_YEAR  ] = false;

	opts->print_inter_zero_values = false;
	opts->print_all_zero_values = false;
	opts->suppress_newline = false;
}

void durfmt(unsigned long duration, const struct durfmt_opts* opts)
{
	bool printed_something = false;
	enum UT last_ut = -1;
	unsigned long vals[UT_MAX] = {0};

	     if (opts->print[UT_SECOND]) last_ut = UT_SECOND;
	else if (opts->print[UT_MINUTE]) last_ut = UT_MINUTE;
	else if (opts->print[UT_HOUR  ]) last_ut = UT_HOUR  ;
	else if (opts->print[UT_DAY   ]) last_ut = UT_DAY   ;
	else if (opts->print[UT_WEEK  ]) last_ut = UT_WEEK  ;
	else if (opts->print[UT_YEAR  ]) last_ut = UT_YEAR  ;

	if (opts->print[UT_YEAR])
	{
		my_div_i(duration, seconds_per[UT_YEAR], &vals[UT_YEAR], &duration);

		if (vals[UT_YEAR] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == UT_YEAR) && opts->print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			printf("%0*lu", opts->width[UT_YEAR], vals[UT_YEAR]);
			putchar(ut_abbr[UT_YEAR]);
			printed_something = true;
		}
	}

	if (opts->print[UT_WEEK])
	{
		my_div_i(duration, seconds_per[UT_WEEK], &vals[UT_WEEK], &duration);

		if (vals[UT_WEEK] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == UT_WEEK) && opts->print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			printf("%0*lu", opts->width[UT_WEEK], vals[UT_WEEK]);
			putchar(ut_abbr[UT_WEEK]);
			printed_something = true;
		}
	}

	if (opts->print[UT_DAY])
	{
		my_div_i(duration, seconds_per[UT_DAY], &vals[UT_DAY], &duration);

		if (vals[UT_DAY] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == UT_DAY) && opts->print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			printf("%0*lu", opts->width[UT_DAY], vals[UT_DAY]);
			putchar(ut_abbr[UT_DAY]);
			printed_something = true;
		}
	}

	if (opts->print[UT_HOUR])
	{
		my_div_i(duration, seconds_per[UT_HOUR], &vals[UT_HOUR], &duration);

		if (vals[UT_HOUR] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == UT_HOUR) && opts->print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			printf("%0*lu", opts->width[UT_HOUR], vals[UT_HOUR]);
			putchar(ut_abbr[UT_HOUR]);
			printed_something = true;
		}
	}

	if (opts->print[UT_MINUTE])
	{
		my_div_i(duration, seconds_per[UT_MINUTE], &vals[UT_MINUTE], &duration);

		if (vals[UT_MINUTE] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == UT_MINUTE) && opts->print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			printf("%0*lu", opts->width[UT_MINUTE], vals[UT_MINUTE]);
			putchar(ut_abbr[UT_MINUTE]);
			printed_something = true;
		}
	}

	if (opts->print[UT_SECOND])
	{
		my_div_i(duration, seconds_per[UT_SECOND], &vals[UT_SECOND], &duration);

		if (vals[UT_SECOND] > 0 || opts->print_all_zero_values || ((printed_something || last_ut == UT_SECOND) && opts->print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			printf("%0*lu", opts->width[UT_SECOND], vals[UT_SECOND]);
			putchar(ut_abbr[UT_SECOND]);
			printed_something = true;
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
	printf("Usage: %s [OPTIONS]\n\n", argv0);
	printf("Read a non-negative duration (in seconds) from stdin.\n");
	printf("Break down the duration into whole numbers of\n");
	printf("  years, weeks, days, hours, minutes, and seconds.\n");
	printf("Values of zero are not printed by default.\n\n");

	printf("OPTIONS\n");
	printf("  -V       Print the version information and exit.\n");
	printf("  -h       Print this message and exit.\n");
	printf("  -n       Do not print a trailing newline character.\n");
	printf("  -p UNITS Specify the units of time to be printed.  Omitted units of time are not printed.\n");
	printf("           If this option is given more than once, only the last occurrence is respected.\n");
	printf("           The default value is 'ywdhms'.\n");
	printf("  -w WIDTH Specify the minimum field width for hours, minutes, and seconds values.\n");
	printf("           If the value of the field has fewer digits than WIDTH, it will be padded with zeros on the left.\n");
	printf("           WIDTH must be a non-negative integer.\n");
	printf("           The default value is 1.\n");
	printf("  -0       Print values of zero.\n");
	printf("           One -0 prints intermediate values of zero (occurring after the most significant printed value).\n");
	printf("           Two -0 prints all values of zero.\n");
	printf("\n");

	printf("  UNIT is a character representing one of the following units of time.\n");
	printf("    y = years\n");
	printf("    w = weeks\n");
	printf("    d = days\n");
	printf("    h = hours\n");
	printf("    m = minutes\n");
	printf("    s = seconds\n");
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
	int width = 1;
	const char* ut_to_print = "ywdhms";
	const char* short_options = "+:Vhnp:w:0";
	int oc;

	durfmt_opts_init(&opts);

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
			width = strtoi(optarg);
			if (width < 0) width = 0;
			if (width > 20) width = 20;
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

	opts.width[UT_SECOND] = width;
	opts.width[UT_MINUTE] = width;
	opts.width[UT_HOUR  ] = width;
	//opts.width[UT_DAY   ] = width;
	//opts.width[UT_WEEK  ] = width;
	//opts.width[UT_YEAR  ] = width;

	while (*ut_to_print)
	{
		switch (tolower(*ut_to_print))
		{
		case 's': opts.print[UT_SECOND] = true; break;
		case 'm': opts.print[UT_MINUTE] = true; break;
		case 'h': opts.print[UT_HOUR  ] = true; break;
		case 'd': opts.print[UT_DAY   ] = true; break;
		case 'w': opts.print[UT_WEEK  ] = true; break;
		case 'y': opts.print[UT_YEAR  ] = true; break;
		default:
			print_option_err(argv[0], "Invalid option value", *ut_to_print);
			return 1;
		}

		++ut_to_print;
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
