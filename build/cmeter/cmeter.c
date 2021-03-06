// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char program_author[] = "Steven Ward";
const char program_version[] = "1.0.0";

const char default_fill = '#';
const char default_unfill = ' ';
const unsigned short default_width = 10;
const unsigned short max_width = 1000;

struct meter_opts
{
	unsigned short width;
	char fill;
	char unfill;
	bool left_to_right;
	bool suppress_newline;
};

void meter_opts_init(struct meter_opts* opts)
{
	opts->width = default_width;
	opts->fill = default_fill;
	opts->unfill = default_unfill;
	opts->left_to_right = true;
	opts->suppress_newline = false;
}

// x is in the interval [0, 1].
void print_cmeter(double x, const struct meter_opts* opts)
{
	// round to nearest int
	const unsigned short num_filled = (unsigned short)(x * opts->width + 0.5);
	const unsigned short num_unfilled = opts->width - num_filled;

	if (opts->left_to_right)
	{
		for (unsigned int i = 0; i < num_filled; ++i)
			putchar(opts->fill);
		for (unsigned int i = 0; i < num_unfilled; ++i)
			putchar(opts->unfill);
	}
	else
	{
		for (unsigned int i = 0; i < num_unfilled; ++i)
			putchar(opts->unfill);
		for (unsigned int i = 0; i < num_filled; ++i)
			putchar(opts->fill);
	}

	if (!opts->suppress_newline)
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
	printf("Read a number (in the interval [0, 1]) from stdin and\n");
	printf("print a meter (filled proportional to the number) using ASCII characters.\n");
	printf("\n");

	printf("OPTIONS\n");
	printf("  -V       Print the version information and exit.\n");
	printf("\n");
	printf("  -h       Print this message and exit.\n");
	printf("\n");
	printf("  -l       Specify that the meter grows from left to right.\n");
	printf("           This is the default behavior.\n");
	printf("\n");
	printf("  -f CHAR  Specify the fill character of the meter.\n");
	printf("           CHAR must be a printable character.\n");
	printf("           The default value is '%c'.\n", default_fill);
	printf("\n");
	printf("  -n       Do not print a trailing newline character.\n");
	printf("\n");
	printf("  -r       Specify that the meter grows from right to left.\n");
	printf("\n");
	printf("  -u CHAR  Specify the unfill character of the meter.\n");
	printf("           CHAR must be a printable character.\n");
	printf("           The default value is '%c'.\n", default_unfill);
	printf("\n");
	printf("  -w WIDTH Specify the width of the meter.\n");
	printf("           WIDTH must be a non-negative integer.\n");
	printf("           The default value is %hu.\n", default_width);
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
	struct meter_opts opts;
	meter_opts_init(&opts);

	int oc;
	const char* short_options = "+:Vhf:lnru:w:";
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

		case 'w':
			opts.width = strtous(optarg);
			if (opts.width > max_width) opts.width = max_width;
			break;

		case 'f':
			opts.fill = optarg[0];
			if (!isprint(opts.fill))
			{
				print_option_err(argv[0], "Invalid option value", opts.fill);
				return 1;
			}
			break;

		case 'u':
			opts.unfill = optarg[0];
			if (!isprint(opts.unfill))
			{
				print_option_err(argv[0], "Invalid option value", opts.unfill);
				return 1;
			}
			break;

		case 'l':
			opts.left_to_right = true;
			break;

		case 'r':
			opts.left_to_right = false;
			break;

		case 'n':
			opts.suppress_newline = true;
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
		double x = strtod(line, NULL);
		if (!isfinite(x))
			continue;
		print_cmeter(clamp(x, 0, 1), &opts);
		free(line);
		line = NULL;
		n = 0;
	}

	return 0;
}
