/**
* @file main.cpp
* @brief Main program that tests the 3 matrix operations : +, - and *
* @authors Walid Slimani, Timothée Van Hove
 */

#include "Matrix/Matrix.hpp"
#include <iostream>

unsigned long parseArg(const char *arg);

int main(int argc, char *argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " <N1> <M1> <N2> <M2> <modulus>\n";
        return EXIT_FAILURE;
    }

    unsigned long N1, M1, N2, M2, modulus;

    try {
        N1 = parseArg(argv[1]);
        M1 = parseArg(argv[2]);
        N2 = parseArg(argv[3]);
        M2 = parseArg(argv[4]);
        modulus = parseArg(argv[5]);
    } catch (const std::runtime_error &e) {
        std::cerr << "Invalid argument: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "The modulus is " << modulus << "\n\n";

    Matrix one((unsigned) N1, (unsigned) M1, (unsigned) modulus);
    Matrix two((unsigned) N2, (unsigned) M2, (unsigned) modulus);

    std::cout << "one\n" << one << "\n";
    std::cout << "two\n" << two << "\n";

    Matrix sum = one + two;
    std::cout << "one + two\n" << sum << "\n";

    Matrix difference = one - two;
    std::cout << "one - two\n" << difference << "\n";

    Matrix product = one * two;
    std::cout << "one x two\n" << product << "\n";

    return EXIT_SUCCESS;
}

/**
 * @brief Parses a command-line argument as a positive integer.
 * @param arg The argument to parse.
 * @return The parsed integer.
 */
unsigned long parseArg(const char *arg) {
    char *end;
    unsigned long value = std::strtoul(arg, &end, 10);
    if (end == arg || *end != '\0') {
        std::cerr << "Invalid argument: " << arg << ". Must be a positive integer.\n";
        std::exit(EXIT_FAILURE);
    }
    return value;
}

