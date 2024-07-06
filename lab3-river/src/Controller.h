/**
 * @file Controller.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_CONTROLLER_H
#define RIVER_CONTROLLER_H

#include "Containers/Container.h"
#include "Containers/Bank.h"
#include "Containers/Boat.h"
#include <unordered_map>
#include <memory>
#include <functional>

/**
 * @class Manages the game state and user input.
 * The Controller is a singleton class that manages the game state, user input and console messages.
 */
class Controller {
public:
    /**
     * @brief Get the singleton instance of the Controller.
     * @return The Controller instance.
     */
    static Controller& getInstance();

    /**
     * @brief Copy constructor is deleted.
     */
    Controller(const Controller&) = delete;

    /**
     * @brief Copy assignment operator is deleted.
     */
    Controller& operator=(const Controller& other) = delete;

    /**
     * @brief Displays the game state to the console.
     */
    void display() const;

    /**
     * @brief Advances the game state by one turn.
     */
    void nextTurn();

    /**
     * @brief Checks if the game has ended.
     * @return true if the game has ended, false otherwise.
     */
    [[nodiscard]] bool hasEnded() const;

    /**
     * @brief Checks if a solution to the game has been found.
     * @return true if the game has been solved, false otherwise.
     */
    [[nodiscard]] bool hasWon() const;

    /**
     * @brief Shows the game menu with command information.
     */
    static void showMenu();

    /**
     * @brief Destructor is defaulted.
     */
    ~Controller() = default;

private:
    /**
     * @brief Construct a new Controller.
     */
    Controller();

    /**
     * @brief Manages the commands entered by the user.
     * @param command The command to manage.
     */
    void manageCommand(const std::string& command);

    /**
     * @brief Moves the boat to the other bank.
     */
    void moveBoat();

    /**
     * @brief Moves a person from one container to another. A person can only be in one container at a time.
     * @param personName The name of the person to move.
     * @param from The container to move the person from.
     * @param to The container to move the person to.
     */
    void movePerson(const std::string& personName, Container& from, Container& to);

    /**
     * @brief Gets the current bank the boat is docked at.
     * @return The current bank.
     */
    Bank& getCurrentBank() const;

    /**
     * @brief Initializes the game state.
     */
    void init();

    /**
     * @brief Resets the game state.
     */
    void reset();

    /**
     * @brief Embarks a person in the boat.
     */
    void embark();

    /**
     * @brief Disembarks a person from the boat.
     */
    void disembark();

    /**
     * @brief Gets the user input.
     * @return The user input.
     */
    static std::string getPrompt();

    /**
     * @brief Displays the bank state to the console.
     * @param bank The bank to display.
     */
    static void displayBank(const Bank& bank);

    /**
     * @brief Prints a diagnostic message to the console.
     * @param diagnostic The diagnostic message to print.
     */
    static void printDiagnostic(const std::string& diagnostic);

    /**
     * @brief Checks if a status is an error. If it's the case, prints the error message.
     * @param status The status to check.
     * @return true if the status is an error, false otherwise.
     */
    static bool isError(const Status& status);

    std::unordered_map<char, std::function<void()>> commandMap;
    std::unique_ptr<Boat> boat;
    std::shared_ptr<Bank> firstBank, secondBank;
    int turn;
    bool ended;
};

#endif //RIVER_CONTROLLER_H
