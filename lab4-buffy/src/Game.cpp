#include <limits>
#include <iostream>
#include "src/Game.hpp"
#include "src/character/Vampire.hpp"
#include "src/character/Human.hpp"
#include "src/Utils.hpp"
#include "src/FieldImpl.hpp"
#include "src/Constants.hpp"

std::mutex Game::mutex;
Game* Game::instance = nullptr;

Game* Game::getInstance(unsigned height, unsigned width, unsigned nbHumans, unsigned nbVampires) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Game(height, width, nbHumans, nbVampires);
    }
    return instance;
}

Game::Game(unsigned int height, unsigned int width, unsigned int nbHumans, unsigned int nbVampires) {
    field = std::make_unique<Field>(height, width, nbHumans, nbVampires);
    displayer = std::make_unique<FieldDisplayer>();
}

void Game::releaseInstance() {
    delete instance;
    instance = nullptr;
}

Game::~Game() = default;

void Game::play() const {
    bool running = true;

    do {
        clearScreen();
        FieldDisplayer::display(*field);

        std::cout << "[" << field->getTurn() << "]" << QUIT_TEXT << " " << STAT_TEXT << " " << NEXT_TEXT
                  << std::endl;

        char userInput;
        std::cin >> userInput;

        if (!std::cin.fail()) {
            switch (userInput) {
                case QUIT_KEY:
                    running = false;
                    break;
                case STAT_KEY:
                    simulate(field->getHeight(),
                        field->getHeight(),
                        field->getNbHumans(),
                        field->getNbVampires()
                    );
                    break;
                case NEXT_KEY:
                    field->nextTurn();
                    break;
                default:
                    break;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (running);
}

void Game::simulate(unsigned height, unsigned width, unsigned nbHumans, unsigned nbVampires) {

    unsigned nbLoses = 0;

    for (unsigned i = 1; i <= SIM_COUNT; ++i) {
        Field simulation(height, width, nbHumans, nbVampires);
        bool hasVampireLeft = true;

        while (hasVampireLeft) {
            hasVampireLeft = simulation.getHumanoidNb<Vampire>() > 0;
            bool hasHumansLeft = simulation.getHumanoidNb<Human>() > 0;

            if (!hasHumansLeft) {
                ++nbLoses;
                break;
            }
            simulation.nextTurn();
        }

        if (i % 1000 == 0) {
            clearScreen();
            double winRate = (1.0 - static_cast<double>(nbLoses) / static_cast<double>(i)) * 100.0;
            std::cout << "[" << i << "] " << WIN_RATE << winRate << '%' << std::endl;
        }
    }
    std::cout << '\n' << ENTER_TEXT;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


