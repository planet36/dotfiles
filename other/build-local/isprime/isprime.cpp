// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <array>
#include <gmpxx.h>
#include <iostream>
#include <string>
#include <string_view>
#include <unistd.h>

constexpr std::string_view program_author = "Steven Ward";
constexpr std::string_view program_version = "1.0.0";
constexpr std::string_view program_license = "OSL-3.0";

constexpr int default_reps = 30;

/// Primality probability category descriptions
constexpr std::array<std::string_view, 3> ppc_descriptions{
    "not ",
    "probably ",
    "",
};

void
print_version()
{
    std::cout << program_invocation_short_name << " " << program_version << '\n';
    std::cout << "License: " << program_license << '\n';
    std::cout << "Written by " << program_author << '\n';
}

void
print_usage()
{
    std::cout << "Usage: " << program_invocation_short_name << " [OPTION]...\n";
    std::cout << '\n';

    std::cout << "Read decimal numbers from stdin, and print whether they are prime or not.\n";
    std::cout << "Invalid trailing characters of the input are ignored.\n";
    std::cout << "The GNU MP function mpz_probab_prime_p is used to test primality.\n";
    std::cout << '\n';

    std::cout << "OPTIONS\n";
    std::cout << "  -V       Print the version information, then exit.\n";
    std::cout << "  -h       Print this message, then exit.\n";
    std::cout << "  -r REPS  Specify the number (less 24) of Miller-Rabin probabilistic primality tests to perform.\n";
    std::cout << "           Reasonable values of REPS are between 15 and 50.\n";
    std::cout << "           The default value is " << default_reps << ".\n";
    std::cout << '\n';

    std::cout << "SEE ALSO\n";
    std::cout << "  https://gmplib.org/manual/Number-Theoretic-Functions#index-mpz_005fprobab_005fprime_005fp\n";
    std::cout << '\n';
}

int
main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    int reps = default_reps;

    int oc;
    const char* short_options = "+:Vhr:";
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

        case 'r':
            try
            {
                reps = std::stoi(optarg);
            }
            catch (const std::invalid_argument& ex)
            {
                std::cerr << "invalid_argument: " << ex.what() << ": " << optarg << '\n';
                return EXIT_FAILURE;
            }
            catch (const std::out_of_range& ex)
            {
                std::cerr << "out_of_range: " << ex.what() << ": " << optarg << '\n';
                return EXIT_FAILURE;
            }

            break;

        default:
            exit(EXIT_FAILURE);
        }
    }

    //argc -= optind;
    //argv += optind;

    mpz_class bn;
    while (std::cin >> bn)
    {
        // primality probability category
        const int ppc = mpz_probab_prime_p(bn.get_mpz_t(), reps);
        std::cout << bn << " is " << ppc_descriptions.at(ppc) << "prime\n";
    }

    return EXIT_SUCCESS;
}
