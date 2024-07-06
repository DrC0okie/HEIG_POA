/**
 * @file ImperialShuttle.hpp
 * @brief Header file defining the ImperialShuttle class representing an imperial shuttle.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef IMPERIAL_SHUTTLE_HPP
#define IMPERIAL_SHUTTLE_HPP

#include "CargoShip.hpp"

class ImperialShuttle : public CargoShip {
private:

    /**
     * @brief Auto-incremented id for the ImperialShuttle.
     */
    static unsigned id;

public:
   /**
     * @brief Value constructor initializing the imperial shuttle with a current load and a nickname.
     * @param currentLoad Current load of the imperial shuttle.
     * @param nickName Nickname of the imperial shuttle.
     */
    explicit ImperialShuttle(double currentLoad = 0, const std::string& nickName = "");

   /**
    * @brief Gets the maximum speed of the imperial shuttle.
    * @return The maximum speed of the imperial shuttle.
    */
    [[nodiscard]] double getMaxSpeed() const override;

   /**
    * @brief Gets the model of the imperial shuttle.
    * @return The model of the imperial shuttle.
    */
    [[nodiscard]] std::string getModel() const override;
};

#endif //IMPERIAL_SHUTTLE_HPP
