/**
 * @file Controller.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include <iostream>
#include <iomanip>
#include <utility>
#include "ControllerConstants.h"
#include "Controller.h"
#include "people/Parent.h"
#include "people/Thief.h"
#include "people/Boy.h"
#include "people/Girl.h"
#include "people/Policeman.h"

Controller::Controller() : boat(std::make_unique<Boat>(BOAT_NAME, BOAT_CAPACITY)),
                           firstBank(std::make_unique<Bank>("gauche")),
                           secondBank(std::make_unique<Bank>("droite")),
                           turn(0), ended(false) {

    init();

    commandMap = {
            {DISPLAY,   [this]() { display(); }},
            {EMBARK,    [this]() { embark(); }},
            {DISEMBARK, [this]() { disembark(); }},
            {MOVE,      [this]() { moveBoat(); }},
            {RESET,     [this]() { reset(); }},
            {QUIT,      [this]() { ended = true; }},
            {MENU,      []() { showMenu(); }}
    };
}

Controller& Controller::getInstance() {
    static Controller instance;
    return instance;
}

void Controller::display() const {
    displayBank(*firstBank);

    if (boat->isDockedAt(*firstBank))
        std::cout << *boat;

    std::cout << std::endl << std::setw(WIDTH) << std::setfill('=') << "" << std::endl;

    if (boat->isDockedAt(*secondBank))
        std::cout << *boat;

    std::cout << std::endl;
    displayBank(*secondBank);
}

void Controller::nextTurn() {
    std::cout << turn << "> ";
    manageCommand(getPrompt());
    turn++;

    if (hasWon()) {
        display();
        std::cout << PROBLEM_SOLVED << std::endl;
        ended = true;
    }

    if (!hasEnded())
        display();
    else
        std::cout << GAME_END << std::endl;
}

bool Controller::hasEnded() const {
    return ended;
}

bool Controller::hasWon() const {
    return firstBank->isEmpty() && boat->isEmpty();
}

void Controller::showMenu() {
    std::cout << DISPLAY << ": afficher\n"
              << EMBARK << " <nom>: embarquer <nom>\n"
              << DISEMBARK << " <nom>: debarquer <nom>\n"
              << MOVE << ": deplacer bateau\n"
              << RESET << ": reinitialiser\n"
              << QUIT << ": quitter\n"
              << MENU << ": menu\n";
}

void Controller::manageCommand(const std::string& command) {
    if (command.length() != 1 || commandMap.find(command[0]) == commandMap.end()) {
        printDiagnostic(INVALID_COMMAND);
        return;
    }
    commandMap[command[0]]();
}

void Controller::moveBoat() {
    if (!boat->hasDriver()) {
        printDiagnostic(BOAT_WITHOUT_DRIVER);
        return;
    }
    boat->dockAt(boat->isDockedAt(*firstBank) ? secondBank : firstBank);
}

void Controller::movePerson(const std::string& personName, Container& from, Container& to) {
    auto person = from.removePerson(personName);
    if (!person) {
        std::string container = from.getName() == BOAT_NAME ? " sur le " : " sur la rive ";
        printDiagnostic(personName + NOT_PRESENT + container + from.getName());
        return;
    }

    // Add person to the container
    to.addPerson(std::move(person));

    // Rollback in case the rules have been violated
    if (isError(getCurrentBank().getStatus()) || isError(boat->getStatus()))
        from.addPerson(to.removePerson(personName));
}

Bank& Controller::getCurrentBank() const {
    return boat->isDockedAt(*firstBank) ? *firstBank : *secondBank;
}

void Controller::init() {
    auto father = std::make_unique<Parent>("pere"), mother = std::make_unique<Parent>("mere");
    auto fatherPtr = father.get(), motherPtr = mother.get();
    auto policeman = std::make_unique<Policeman>("policier");
    firstBank->addPerson(std::make_unique<Boy>("paul", fatherPtr, motherPtr));
    firstBank->addPerson(std::make_unique<Boy>("pierre", fatherPtr, motherPtr));
    firstBank->addPerson(std::make_unique<Girl>("julie", fatherPtr, motherPtr));
    firstBank->addPerson(std::make_unique<Girl>("jeanne", fatherPtr, motherPtr));
    firstBank->addPerson(std::make_unique<Thief>("voleur", policeman.get()));
    firstBank->addPerson(std::move(father));
    firstBank->addPerson(std::move(mother));
    firstBank->addPerson(std::move(policeman));

    boat->dockAt(firstBank);
    turn = 0;
}

void Controller::reset() {
    firstBank->clear();
    secondBank->clear();
    boat->clear();
    init();
}

void Controller::embark() {
    if (boat->isFull())
        printDiagnostic(BOAT_FULL);
    else
        movePerson(getPrompt(), getCurrentBank(), *boat);
}

void Controller::disembark() {
    movePerson(getPrompt(), *boat, getCurrentBank());
}

std::string Controller::getPrompt() {
    std::string name;
    std::cin >> name;
    return name;
}

void Controller::displayBank(const Bank& bank) {
    std::cout << std::setw(WIDTH) << std::setfill('-') << "" << std::endl
              << bank << std::endl
              << std::setw(WIDTH) << std::setfill('-') << "" << std::endl;
}

void Controller::printDiagnostic(const std::string& diagnostic) {
    std::cout << "### " << diagnostic << std::endl;
}

bool Controller::isError(const Status& status) {
    if (status.error) {
        printDiagnostic(status.diagnostic);
        return true;
    }
    return false;
}
