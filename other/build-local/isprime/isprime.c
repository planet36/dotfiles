// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <openssl/bn.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char* program_author = "Steven Ward";
const char* program_version = "1.0.0";
const char* program_license = "OSL-3.0";

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

	printf("Read decimal numbers from stdin, and print whether they are prime or not.\n");
	printf("Invalid trailing characters of the input are ignored.\n");
	printf("The OpenSSL function BN_check_prime is used to test primality.\n");
	printf("The format of the output is designed to be the same as the OpenSSL program openssl-prime.\n");
	printf("\n");

	printf("OPTIONS\n");
	printf("  -V       Print the version information, then exit.\n");
	printf("  -h       Print this message, then exit.\n");
	printf("  -x       Read the input as hexadecimal instead of decimal.\n");
	printf("\n");

	printf("SEE ALSO\n");
	printf("  https://www.openssl.org/docs/manmaster/man3/BN_check_prime.html\n");
	printf("  https://www.openssl.org/docs/manmaster/man1/openssl-prime.html\n");
	printf("\n");
}

int
main(int argc, char* const argv[])
{
	bool hex = false;

	int oc;
	const char* short_options = "+:Vhx";
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

		case 'x':
			hex = true;
			break;

		default:
			exit(EXIT_FAILURE);
		}
	}

	//argc -= optind;
	//argv += optind;

	BIGNUM *bn = nullptr;

	char* buf = nullptr;
	size_t buf_size = 0;
	ssize_t bytes_read = 0;

	while ((bytes_read = getline(&buf, &buf_size, stdin)) != -1)
	{
		const int result = (hex ? BN_hex2bn(&bn, buf) : BN_dec2bn(&bn, buf));
		if (result != 0)
		{
			const bool is_prime = BN_check_prime(bn, nullptr, nullptr);
			BN_print_fp(stdout, bn);
			printf(" (%.*s) %s prime\n", result, buf, is_prime ? "is" : "is not");
		}
	}
	free(buf);
	BN_clear_free(bn);

	return EXIT_SUCCESS;
}
