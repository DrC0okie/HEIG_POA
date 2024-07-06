/**
 * @file StarDreadnought.hpp
 * @brief Header file defining the StarDreadnought class representing a star dreadnought ship.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef STAR_DREADNOUGHT_HPP
#define STAR_DREADNOUGHT_HPP

#include "CargoShip.hpp"

class StarDreadnought : public CargoShip {
private:

    /**
     * @brief Auto-incremented id for the star dreadnought.
     */
    static unsigned id;

public:
   /**
     * @brief Value constructor initializing the star dreadnought with a current load and a nickname.
     * @param currentLoad Current load of the star dreadnought.
     * @param nickName Nickname of the star dreadnought.
     */
    explicit StarDreadnought(double currentLoad = 0, const std::string& nickName = "");

   /**
    * @brief Gets the maximum speed of the star dreadnought.
    * @return The maximum speed of the star dreadnought.
    */
    [[nodiscard]] double getMaxSpeed() const override;

   /**
    * @brief Gets the model of the star dreadnought.
    * @return The model of the star dreadnought.
    */
    [[nodiscard]] std::string getModel() const override;
};

#endif //STAR_DREADNOUGHT_HPP
