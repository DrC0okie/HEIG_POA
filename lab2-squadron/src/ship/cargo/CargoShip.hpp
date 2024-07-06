/**
 * @file CargoShip.hpp
 * @brief Header file defining the CargoShip class representing a cargo ship.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef CARGO_SHIP_HPP
#define CARGO_SHIP_HPP

#include "../Ship.hpp"

class CargoShip : public Ship {
private:
    double currentLoad = 0;
    double baseWeight;
    double maxLoad;

protected:
   /**
     * @brief Value constructor initializing with a base weight, a maximum load capacity, a current load and a nickname.
     * @param baseWeight Base weight of the cargo ship.
     * @param maxLoad Maximum load capacity of the cargo ship.
     * @param currentLoad Current load of the cargo ship.
     * @param nickName Nickname of the cargo ship.
     * @throws std::invalid_argument If the base weight, maximum load or current load is negative
     * or if the current load is greater than the maximum load capacity.
     */
    explicit CargoShip(double baseWeight, double maxLoad, double currentLoad = 0,
                       const std::string& nickName = "");

public:
   /**
     * @brief Destructor for the CargoShip object.
     */
    ~CargoShip() noexcept override;

   /**
    * @brief Formats the cargo ship information to an output stream.
    * @param os Output stream.
    * @return The formatted output stream.
    */
    std::ostream& formatToStream(std::ostream& os) const override;

   /**
    * @brief Gets the weight of the cargo ship.
    * @return The weight of the cargo ship (base weight + current load).
    */
    [[nodiscard]] double getWeight() const override;

   /**
    * @brief Sets the current load of the cargo ship.
    * @param load The current load to set.
    * @throws std::invalid_argument If the load is negative or greater than the maximum load capacity.
    */
    void setLoad(double load);
};

#endif //CARGO_SHIP_HPP
