// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char program_author[] = "Steven Ward";
const char program_version[] = "21w15d"; // date +'%yw%Ua'

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

void durfmt(
		unsigned long seconds,
		const bool print_zero_values,
		const bool suppress_newline)
{
	bool printed_something = false;
	unsigned long years = 0;
	unsigned long weeks = 0;
	unsigned long days = 0;
	unsigned long hours = 0;
	unsigned long minutes = 0;

	{
		my_div_i(seconds, seconds_per_year, &years, &seconds);

		if (years > 0 || print_zero_values)
		{
			if (printed_something)
				putchar(' ');
			printf("%luy", years);
			printed_something = true;
		}
	}

	{
		my_div_i(seconds, seconds_per_week, &weeks, &seconds);

		if (weeks > 0 || print_zero_values)
		{
			if (printed_something)
				putchar(' ');
			printf("%luw", weeks);
			printed_something = true;
		}
	}

	{
		my_div_i(seconds, seconds_per_day, &days, &seconds);

		if (days > 0 || print_zero_values)
		{
			if (printed_something)
				putchar(' ');
			printf("%lud", days);
			printed_something = true;
		}
	}

	{
		my_div_i(seconds, seconds_per_hour, &hours, &seconds);

		if (hours > 0 || print_zero_values)
		{
			if (printed_something)
				putchar(' ');
			printf("%luh", hours);
			printed_something = true;
		}
	}

	{
		my_div_i(seconds, seconds_per_minute, &minutes, &seconds);

		if (minutes > 0 || print_zero_values)
		{
			if (printed_something)
				putchar(' ');
			printf("%lum", minutes);
			printed_something = true;
		}
	}

	{
		if (seconds > 0 || print_zero_values)
		{
			if (printed_something)
				putchar(' ');
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
	printf("  -n       Do not print a trailing newline character.\n");
	printf("  -0       Print values of zero.\n");
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
	bool print_zero_values = false;
	bool suppress_newline = false;
	unsigned long round_mult = 1;
	const char* short_options = "+:Vhl:n0";
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
			case 'Y': case 'y': round_mult = seconds_per_year  ; break;
			case 'W': case 'w': round_mult = seconds_per_week  ; break;
			case 'D': case 'd': round_mult = seconds_per_day   ; break;
			case 'H': case 'h': round_mult = seconds_per_hour  ; break;
			case 'M': case 'm': round_mult = seconds_per_minute; break;
			case 'S': case 's': round_mult =                  1; break;
			default:
				print_option_err(argv[0], "Unknown option value", optarg[0]);
				return 1;
			}
			break;

		case 'n':
			suppress_newline = true;
			break;

		case '0':
			print_zero_values = true;
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

	char* line = NULL;
	size_t n = 0;
	//ssize_t bytes_read = 0;
	//while ((bytes_read = getline(&line, &n, stdin)) != EOF)
	while (getline(&line, &n, stdin) != EOF)
	{
		unsigned long seconds = strtoul(line, NULL, 0);
		if (round_mult > 1)
			seconds -= (seconds % round_mult);
		durfmt(seconds, print_zero_values, suppress_newline);
		free(line);
		line = NULL;
		n = 0;
	}

	return 0;
}
