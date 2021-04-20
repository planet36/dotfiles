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
	UT_HOUR,
	UT_DAY,
	UT_WEEK,
	UT_YEAR,
	UT_MAX, // must be last
};

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

const unsigned long seconds_per_minute = 60UL;
const unsigned long seconds_per_hour = seconds_per_minute * 60UL;
const unsigned long seconds_per_day = seconds_per_hour * 24UL;
const unsigned long seconds_per_week = seconds_per_day * 7UL;
const unsigned long seconds_per_year = 31556952UL; // seconds_per_day * 365.2425

struct durfmt_opts
{
	int w_s;
	int w_m;
	int w_h;
	int w_d;
	int w_w;
	int w_y;

	char u_s;
	char u_m;
	char u_h;
	char u_d;
	char u_w;
	char u_y;

	bool p_s;
	bool p_m;
	bool p_h;
	bool p_d;
	bool p_w;
	bool p_y;

	bool p_0s;
	bool p_0m;
	bool p_0h;
	bool p_0d;
	bool p_0w;
	bool p_0y;
};

void durfmt_opts_init(struct durfmt_opts* opts)
{
	opts->w_s = 1;
	opts->w_m = 1;
	opts->w_h = 1;
	opts->w_d = 1;
	opts->w_w = 1;
	opts->w_y = 1;

	opts->u_s = 's';
	opts->u_m = 'm';
	opts->u_h = 'h';
	opts->u_d = 'd';
	opts->u_w = 'w';
	opts->u_y = 'y';

	opts->p_s = true;
	opts->p_m = true;
	opts->p_h = true;
	opts->p_d = true;
	opts->p_w = true;
	opts->p_y = true;

	opts->p_0s = false;
	opts->p_0m = false;
	opts->p_0h = false;
	opts->p_0d = false;
	opts->p_0w = false;
	opts->p_0y = false;
}

void durfmt(
		unsigned long seconds,
		const int width,
		const enum UT least_sig,
		const enum UT most_sig,
		const bool print_all_zero_values,
		const bool print_inter_zero_values,
		const bool suppress_newline)
{
	bool printed_something = false;
	unsigned long years = 0;
	unsigned long weeks = 0;
	unsigned long days = 0;
	unsigned long hours = 0;
	unsigned long minutes = 0;

	if (least_sig <= UT_YEAR && most_sig >= UT_YEAR)
	{
		my_div_i(seconds, seconds_per_year, &years, &seconds);

		if (years > 0 || print_all_zero_values || (printed_something && print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			if (width > 1)
				printf("%0*luy", width, years);
			else
				printf("%luy", years);
			printed_something = true;
		}
	}

	if (least_sig <= UT_WEEK && most_sig >= UT_WEEK)
	{
		my_div_i(seconds, seconds_per_week, &weeks, &seconds);

		if (weeks > 0 || print_all_zero_values || (printed_something && print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			if (width > 1)
				printf("%0*luw", width, weeks);
			else
				printf("%luw", weeks);
			printed_something = true;
		}
	}

	if (least_sig <= UT_DAY && most_sig >= UT_DAY)
	{
		my_div_i(seconds, seconds_per_day, &days, &seconds);

		if (days > 0 || print_all_zero_values || (printed_something && print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			if (width > 1)
				printf("%0*lud", width, days);
			else
				printf("%lud", days);
			printed_something = true;
		}
	}

	if (least_sig <= UT_HOUR && most_sig >= UT_HOUR)
	{
		my_div_i(seconds, seconds_per_hour, &hours, &seconds);

		if (hours > 0 || print_all_zero_values || (printed_something && print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			if (width > 1)
				printf("%0*luh", width, hours);
			else
				printf("%luh", hours);
			printed_something = true;
		}
	}

	if (least_sig <= UT_MINUTE && most_sig >= UT_MINUTE)
	{
		my_div_i(seconds, seconds_per_minute, &minutes, &seconds);

		if (minutes > 0 || print_all_zero_values || (printed_something && print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			if (width > 1)
				printf("%0*lum", width, minutes);
			else
				printf("%lum", minutes);
			printed_something = true;
		}
	}

	if (least_sig <= UT_SECOND && most_sig >= UT_SECOND)
	{
		if (seconds > 0 || print_all_zero_values || (printed_something && print_inter_zero_values))
		{
			if (printed_something)
				putchar(' ');
			if (width > 1)
				printf("%0*lus", width, seconds);
			else
				printf("%lus", seconds);
			printed_something = true;
		}
	}

	if (printed_something && !suppress_newline)
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
	printf("  -l UNIT  Specify the least significant unit of time to be printed.\n");
	printf("           UNIT must not be greater than the most significant unit of time.\n");
	printf("           The default value is 's'.\n");
	printf("  -m UNIT  Specify the most significant unit of time to be printed.\n");
	printf("           UNIT must not be less than the least significant unit of time.\n");
	printf("           The default value is 'y'.\n");
	printf("  -n       Do not print a trailing newline character.\n");
	printf("  -w WIDTH Specify the minimum field width.\n");
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
	int width = 1;
	bool print_inter_zero_values = false;
	bool print_all_zero_values = false;
	enum UT least_sig = UT_SECOND;
	enum UT most_sig = UT_YEAR;
	bool suppress_newline = false;
	const char* short_options = "+:Vhl:m:nw:0";
	int oc;

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

		case 'l':
			switch (optarg[0])
			{
			case 'Y': case 'y': least_sig = UT_YEAR  ; break;
			case 'W': case 'w': least_sig = UT_WEEK  ; break;
			case 'D': case 'd': least_sig = UT_DAY   ; break;
			case 'H': case 'h': least_sig = UT_HOUR  ; break;
			case 'M': case 'm': least_sig = UT_MINUTE; break;
			case 'S': case 's': least_sig = UT_SECOND; break;
			default:
				print_option_err(argv[0], "Unknown option value", optarg[0]);
				return 1;
			}
			break;

		case 'm':
			switch (optarg[0])
			{
			case 'Y': case 'y': most_sig = UT_YEAR  ; break;
			case 'W': case 'w': most_sig = UT_WEEK  ; break;
			case 'D': case 'd': most_sig = UT_DAY   ; break;
			case 'H': case 'h': most_sig = UT_HOUR  ; break;
			case 'M': case 'm': most_sig = UT_MINUTE; break;
			case 'S': case 's': most_sig = UT_SECOND; break;
			default:
				print_option_err(argv[0], "Unknown option value", optarg[0]);
				return 1;
			}
			break;

		case 'n':
			suppress_newline = true;
			break;

		case 'w':
			width = strtoi(optarg);
			if (width < 0) width = 0;
			if (width > 20) width = 20;
			break;

		case '0':
			if (print_inter_zero_values)
			{
				print_all_zero_values = true;
			}
			else
			{
				print_inter_zero_values = true;
			}
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

	if (most_sig < least_sig)
	{
		fprintf(stderr, "%s: Invalid option values: -m UNIT may not be less than -l UNIT\n", argv[0]);
		return 1;
	}

	//argc -= optind;
	//argv += optind;

	char* line = NULL;
	size_t n = 0;
	//ssize_t bytes_read = 0;
	//while ((bytes_read = getline(&line, &n, stdin)) != EOF)
	while (getline(&line, &n, stdin) != EOF)
	{
		unsigned long seconds = strtoul(line, NULL, 0);
		durfmt(seconds, width, least_sig, most_sig, print_all_zero_values, print_inter_zero_values, suppress_newline);
		free(line);
		line = NULL;
		n = 0;
	}

	return 0;
}
