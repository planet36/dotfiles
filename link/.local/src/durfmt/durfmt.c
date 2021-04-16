// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char program_author[] = "Steven Ward";
const char program_version[] = "21w15b"; // date +'%yw%Ua'

void my_div_i(
		const unsigned long x, const unsigned long y,
		unsigned long* quo, unsigned long* rem)
{
	*quo = (x / y);
	*rem = (x % y);
}

const unsigned long seconds_per_minute = 60U;
const unsigned long seconds_per_hour = seconds_per_minute * 60U;
const unsigned long seconds_per_day = seconds_per_hour * 24U;
const unsigned long seconds_per_week = seconds_per_day * 7U;
const unsigned long seconds_per_year = 31556952U; // seconds_per_day * 365.2425

void durfmt(unsigned long seconds, const bool print_zero_seconds)
{
	bool printed_something = false;
	unsigned long years = 0;
	unsigned long weeks = 0;
	unsigned long days = 0;
	unsigned long hours = 0;
	unsigned long minutes = 0;

	my_div_i(seconds, seconds_per_year, &years, &seconds);
	my_div_i(seconds, seconds_per_week, &weeks, &seconds);
	my_div_i(seconds, seconds_per_day, &days, &seconds);
	my_div_i(seconds, seconds_per_hour, &hours, &seconds);
	my_div_i(seconds, seconds_per_minute, &minutes, &seconds);

	if (years > 0)
	{
		if (printed_something)
			putchar(' ');
		printf("%luy", years);
		printed_something = true;
	}

	if (weeks > 0)
	{
		if (printed_something)
			putchar(' ');
		printf("%luw", weeks);
		printed_something = true;
	}

	if (days > 0)
	{
		if (printed_something)
			putchar(' ');
		printf("%lud", days);
		printed_something = true;
	}

	if (hours > 0)
	{
		if (printed_something)
			putchar(' ');
		printf("%luh", hours);
		printed_something = true;
	}

	if (minutes > 0)
	{
		if (printed_something)
			putchar(' ');
		printf("%lum", minutes);
		printed_something = true;
	}

	if (seconds > 0 || (print_zero_seconds && !printed_something))
	{
		if (printed_something)
			putchar(' ');
		printf("%lus", seconds);
		printed_something = true;
	}

	if (printed_something)
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
	printf("Break down the value into whole numbers of\n");
	printf("  years, weeks, days, hours, minutes, and seconds.\n\n");
	printf("OPTIONS\n");
	printf("  -V    Print the version information and exit.\n");
	printf("  -h    Print this message and exit.\n");
	printf("  -0    Print zero seconds if nothing else was printed.\n");
	printf("  -r[ywdhm]\n");
	printf("        Round the duration down to the nearest multiple of\n");
	printf("          [y]ears, [w]eeks, [d]ays, [h]ours, or [m]inutes.\n");
	printf("\n");
}

int main(int argc, char* argv[])
{
	bool print_zero_seconds = false;
	unsigned long round_mult = 0;
	const char* short_options = "+:Vh0r:";
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

		case '0':
			print_zero_seconds = true;
			break;

		case 'r':
			switch (optarg[0])
			{
			case 'Y': case 'y': round_mult = seconds_per_year  ; break;
			case 'W': case 'w': round_mult = seconds_per_week  ; break;
			case 'D': case 'd': round_mult = seconds_per_day   ; break;
			case 'H': case 'h': round_mult = seconds_per_hour  ; break;
			case 'M': case 'm': round_mult = seconds_per_minute; break;
			default:
				if (isprint(optarg[0]))
					fprintf(stderr, "%s: Unknown option value: '%c'\n", argv[0], optarg[0]);
				else
					fprintf(stderr, "%s: Unknown option value: '\\x%x'\n", argv[0], optarg[0]);
				return 1;
			}
			break;

		case '?':
			if (isprint(optopt))
				fprintf(stderr, "%s: Unknown option: '%c'\n", argv[0], optopt);
			else
				fprintf(stderr, "%s: Unknown option: '\\x%x'\n", argv[0], optopt);
			return 1;

		case ':':
			if (isprint(optopt))
				fprintf(stderr, "%s: Option requires a value: '%c'\n", argv[0], optopt);
			else
				fprintf(stderr, "%s: Option requires a value: '\\x%x'\n", argv[0], optopt);
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
		if (round_mult != 0)
			seconds -= (seconds % round_mult);
		durfmt(seconds, print_zero_seconds);
		free(line);
		line = NULL;
		n = 0;
	}

	return 0;
}
