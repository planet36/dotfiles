// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

#include <array>
#include <cerrno>
#include <cstdlib>
#include <err.h>
#include <gmpxx.h>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unistd.h>

inline constexpr std::string_view program_author = "Steven Ward";
inline constexpr std::string_view program_version = "1.0.1";
inline constexpr std::string_view program_license = "MPL-2.0";

inline constexpr int default_reps = 30;

/// Primality probability category descriptions
inline constexpr std::array<std::string_view, 3> ppc_descriptions{
    "not ",
    "probably ",
    "",
};

void
print_version()
{
    std::println("{} {}", program_invocation_short_name, program_version);
    std::println("License: {}", program_license);
    std::println("Written by {}", program_author);
}

void
print_usage()
{
    std::println("Usage: {} [OPTION]...", program_invocation_short_name);
    std::println();

    std::println("Read decimal numbers from stdin, and print whether they are prime or not.");
    std::println("Reading stops silently at the first invalid token; the exit status");
    std::println("becomes non-zero and any later input is not processed.");
    std::println("The GNU MP function mpz_probab_prime_p is used to test primality.");
    std::println();

    std::println("OPTIONS");
    std::println("  -V       Print the version information, then exit.");
    std::println("  -h       Print this message, then exit.");
    std::println("  -r REPS  Specify the number of Miller-Rabin probabilistic primality tests to");
    std::println("           perform (REPS - 24, after built-in trial division and a");
    std::println("           Baillie-PSW test).");
    std::println("           Reasonable values of REPS are between 15 and 50.");
    std::println("           The default value is {}.", default_reps);
    std::println();

    std::println("SEE ALSO");
    std::println("  https://gmplib.org/manual/Number-Theoretic-Functions"
                 "#index-mpz_005fprobab_005fprime_005fp");
    std::println();
}

int
// NOLINTNEXTLINE(bugprone-exception-escape)
main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    int reps = default_reps;

    int oc = 0;
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
                errx(EXIT_FAILURE, "invalid argument: %s: \"%s\"", ex.what(), optarg);
            }
            catch (const std::out_of_range& ex)
            {
                errx(EXIT_FAILURE, "out of range: %s: \"%s\"", ex.what(), optarg);
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
        std::println("{} is {}prime", bn.get_str(), ppc_descriptions.at(ppc));
    }

    if (std::cin.bad() || (std::cin.fail() && !std::cin.eof()))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
