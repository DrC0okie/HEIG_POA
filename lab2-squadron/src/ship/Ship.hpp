/**
 * @file Ship.hpp
 * @brief Header file defining the Ship class representing a generic ship.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef SHIP_HPP
#define SHIP_HPP

#include <ostream>
#include <string>

class Ship;

/**
 * @brief Stream insertion operator to print the ship information to an output stream.
 * @param os Output stream.
 * @param ship Ship object to print.
 * @return The output stream with the ship information printed.
 */
std::ostream& operator<<(std::ostream& os, const Ship& ship);

class Ship {
private:
    std::string nickname;

protected:
   /**
     * @brief Value constructor initializing the Ship with a nickname.
     * @param nickname Nickname of the ship.
     */
    explicit Ship(std::string nickname);


    /**
     * @brief Unique identifier of the ship.
     */
    unsigned instanceId = 0;

public:
   /**
     * @brief Destructor for the Ship object.
     */
    virtual ~Ship() noexcept;

   /**
    * @brief Sets the nickname of the ship.
    * @param nick Nickname to set.
    */
    void setNickname(const std::string& name);

   /**
    * @brief Gets the nickname of the ship.
    * @return The nickname of the ship.
    */
    [[nodiscard]] std::string getNickname() const;

   /**
    * @brief Calculates the fuel consumption of the ship for a given distance and speed.
    * @param distance Distance to travel.
    * @param speed Speed of travel.
    * @return The fuel consumption of the ship.
    * @throws std::invalid_argument If the distance or speed is negative or if the speed exceeds the max speed of the ship.
    */
    [[nodiscard]] double getConsumption(double distance, double speed) const;

   /**
    * @brief Gets the unique identifier of the ship.
    * @return The unique identifier of the ship.
    */
    [[nodiscard]] double getId() const;

   /**
    * @brief Gets the maximum speed of the ship.
    * @return The maximum speed of the ship.
    */
    [[nodiscard]] virtual double getMaxSpeed() const = 0;

   /**
    * @brief Gets the weight of the ship.
    * @return The weight of the ship.
    */
    [[nodiscard]] virtual double getWeight() const = 0;

   /**
    * @brief Gets the model of the ship.
    * @return The model of the ship.
    */
    [[nodiscard]] virtual std::string getModel() const = 0;

   /**
    * @brief Formats the ship information to an output stream.
    * @param os Output stream.
    * @return The formatted output stream.
    */
    [[nodiscard]] virtual std::ostream& formatToStream(std::ostream& os) const;
};

#endif //SHIP_HPP
