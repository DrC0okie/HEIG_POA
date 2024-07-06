#ifndef POA_LABO4_GAME_HPP
#define POA_LABO4_GAME_HPP

#include <ctime>
#include "Field.hpp"
#include "src/gui/FieldDisplayer.hpp"

/**
 * Singleton class for managing a Buffy game & simulation
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Game {
private:

    /**
     * Create a new game
     * @param height height of the board
     * @param width width of the board
     * @param nbHumans number of humans
     * @param nbVampires number of vampires
     */
    Game(unsigned height, unsigned width, unsigned nbHumans, unsigned nbVampires);

    /**
     * Simulate a number of games
     * @param height height of the board
     * @param width width of the board
     * @param nbHumans number of humans
     * @param nbVampires number of vampires
     */
    static void simulate(unsigned height, unsigned width, unsigned nbHumans, unsigned nbVampires);

    /**
     * Destruct the game
     */
    ~Game();

    static Game* instance;

    static std::mutex mutex;

    std::unique_ptr<Field> field;

    std::unique_ptr<FieldDisplayer> displayer;

public:

    /**
     * Gets the instance of the game
     * @param height height of the board
     * @param width width of the board
     * @param nbHumans number of humans
     * @param nbVampires number of vampires
     * @return the instance of the game
     */
    static Game* getInstance(unsigned height = 0, unsigned width = 0, unsigned nbHumans = 0, unsigned nbVampires = 0);

    static void releaseInstance();

    /**
     * Start the game interaction
     */
    void play() const;
};

#endif //POA_LABO4_GAME_HPP
