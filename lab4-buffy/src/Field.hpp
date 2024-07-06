#ifndef POA_LABO4_FIELD_HPP
#define POA_LABO4_FIELD_HPP

#include <list>
#include <random>
#include <typeinfo> // typeid
#include "src/character/Humanoid.hpp"

class Humanoid;

/**
 * Class that represent the game field on which the entities will move
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Field {
private:
    unsigned height, width, nbHumans, nbVampires, turn = 0;
    mutable std::mt19937 engine;
    std::list<std::unique_ptr<Humanoid>> humanoids;

public:
    /**
     * Create a new field
     * @param height height of field
     * @param width width of field
     * @param nbHumans number of human to add on the field
     * @param nbVampires number of vampires to add on the field
     */
    Field(unsigned height, unsigned width, unsigned nbHumans, unsigned nbVampires);

    /**
     * Destruct the field
     */
    ~Field();

    /**
     * Get the height of the field
     * @return height of the field
     */
    [[nodiscard]] unsigned getHeight() const;

    /**
     * Get the width of the field
     * @return width of the field
     */
    [[nodiscard]] unsigned getWidth() const;

    /**
    * Get the number of humans on the field
    * @return number of humans
    */
    [[nodiscard]] unsigned getNbHumans() const;

    /**
    * Get the number of vampires on the field
    * @return number of vampires
    */
    [[nodiscard]] unsigned getNbVampires() const;

    /**
     * Run the next round of the simulation
     * @return next round's number
     */
    unsigned nextTurn();

    /**
     * Get the current turn's number
     * @return current turn's number
     */
    [[nodiscard]] unsigned getTurn() const;

    /**
     * Get the random engine
     * @return random engin
     */
    [[nodiscard]] std::mt19937& getRandomEngine() const;

    /**
     * Get the humanoids on the field as a 2D array
     * @return humanoids on the field
     */
    [[nodiscard]] std::vector<Humanoid*> getHumanoid2DVector() const;

    /**
     * Add an humanoid to the field
     * @param h humanoid to add
     */
    void add(std::unique_ptr<Humanoid> humanoid);

    /**
     * Get the closest humanoid from an humanoid
     * @tparam T exact type of humanoid to search
     * @param humanoid the humanoid to use for distance to
     * @return closest humanoid type if it exists, else nullptr
     */
    template <class T>
    T* getClosestHumanoid(Humanoid* humanoid) const;

    /**
     * Get the number of alive humanoid on the field
     *
     * @tparam T exact type of humanoid to search
     * @return number of humanoid type on the field
     */
    template <class T>
    [[nodiscard]] unsigned getHumanoidNb() const;

};

#endif //POA_LABO4_FIELD_HPP
