/**
 * @file main.cpp Entry point of the program
 * @authors Walid Slimani, Timothée Van Hove
 */

#include <iostream>
#include <string>
#include "Game.hpp"

// Function declarations
static unsigned parseArg(const std::string& arg);
void printUsage(const std::string& programName);
std::string getExecutableName(const std::string& path);

int main(int argc, char** argv) {
    unsigned height, width, nbHumans, nbVampires;

    std::string executableName = getExecutableName(argv[0]);

    // Parse user arguments or use default values
    if (argc == 5) {
        try {
            height = parseArg(argv[1]);
            width = parseArg(argv[2]);
            nbHumans = parseArg(argv[3]);
            nbVampires = parseArg(argv[4]);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            printUsage(executableName);
            return EXIT_FAILURE;
        }
    } else if (argc == 1) {
        height = DEFAULT_HEIGHT;
        width = DEFAULT_WIDTH;
        nbHumans = DEFAULT_NB_HUMANS;
        nbVampires = DEFAULT_NB_VAMPIRES;
    } else {
        printUsage(executableName);
        return EXIT_FAILURE;
    }

    // Run the game
    Game* game = Game::getInstance(height, width, nbHumans, nbVampires);
    game->play();
    Game::releaseInstance();

    return EXIT_SUCCESS;
}

static unsigned parseArg(const std::string& arg) {
    try {
        return std::stoul(arg);
    } catch (const std::exception& e) {
        std::cerr << "Invalid number: " << arg << ". Please enter a valid unsigned integer." << std::endl;
        throw;
    }
}

void printUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " <height> <width> <nbHumans> <nbVampires>\n"
              << "All parameters are required and must be unsigned integers.\n"
              << "Example: " << programName << " 10 10 20 5\n";
}

std::string getExecutableName(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    return (pos == std::string::npos) ? path : path.substr(pos + 1);
}
