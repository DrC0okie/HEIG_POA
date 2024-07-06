/**
 * @file main.cpp
 * @brief Entry point of the program
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Controller.h"

int main() {
    Controller& controller = Controller::getInstance();
    Controller::showMenu();
    controller.display();

    while (!controller.hasEnded())
        controller.nextTurn();

    return EXIT_SUCCESS;
}