/**
 * @file Squadron.hpp
 * @brief Header file defining a class for managing squadrons of ships.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef SQUADRON_HPP
#define SQUADRON_HPP

#include <memory>
#include "../ship/Ship.hpp"
#include "../utils/ShipList.hpp"
#include <string>

class Squadron;

/**
 * @brief Overloaded addition operator to add a ship to a squadron.
 * @param squadron Squadron to add the ship to.
 * @param ship Ship to add to the squadron.
 * @return The updated squadron after adding the ship.
 */
Squadron operator+(const Squadron& squadron, Ship& ship);

/**
 * @brief Overloaded addition operator to add a ship to a squadron.
 * @param ship Ship to add to the squadron.
 * @param squadron Squadron to add the ship to.
 * @return The updated squadron after adding the ship.
 */
Squadron operator+(Ship& ship, const Squadron& squadron);

/**
 * @brief Overloaded subtraction operator to remove a ship from a squadron.
 * @param squadron Squadron to remove the ship from.
 * @param ship Ship to remove from the squadron.
 * @return The updated squadron after removing the ship.
 */
Squadron operator-(const Squadron& squadron, Ship& ship);

/**
 * @brief Overloaded stream insertion operator to output a squadron.
 * @param os Output stream.
 * @param squad Squadron to output.
 * @return The output stream containing the formatted squadron.
 */
std::ostream& operator<<(std::ostream& os, const Squadron& squad);

class Squadron {

private:

    /**
     * @brief Name of the squadron.
     */
    std::string name;

    /**
     * @brief Leader ship of the squadron.
     */
    Ship* leader{};

    /**
     * @brief List of member ships in the squadron.
     */
    ShipList members;

   /**
    * @brief Prints a formatted header with a given name.
    * @param os String to print.
    * @return Formatted header string.
    */
    [[nodiscard]] static std::string printHeader(const std::string& os);

   /**
    * @brief Exchanges (moves) this squadron with another.
    * @param other Squadron to exchange with.
    */
    void exchange(Squadron& other);

   /**
    * @brief Copies the values of another squadron.
    * @param other Squadron to copy.
    */
    void copy(const Squadron& other);

public:
   /**
     * @brief Constructor with name parameter.
     * @param name Name of the squadron.
     */
    explicit Squadron(std::string name);

   /**
    * @brief Copy constructor.
    * @param other Squadron to copy.
    */
    Squadron(const Squadron& other);

   /**
    * @brief Move constructor.
    * @param other Squadron to move from.
    */
    Squadron(Squadron&& other) noexcept;

   /**
    * @brief Destructor.
    */
    ~Squadron();

   /**
    * @brief Copy assignment operator.
    * @param other Squadron to assign from.
    * @return Reference to the assigned squadron.
    */
    Squadron& operator=(const Squadron& other);

   /**
    * @brief Move assignment operator.
    * @param other Squadron to move from.
    * @return Reference to the moved squadron.
    */
    Squadron& operator=(Squadron&& other) noexcept;

   /**
    * @brief Overloaded compound addition assignment operator to add a ship to the squadron.
    * @param ship Ship to add to the squadron.
    * @return A reference to the updated squadron after adding the ship.
    */
    Squadron& operator+=(Ship& ship);

   /**
    * @brief Overloaded compound subtraction assignment operator to remove a ship from the squadron.
    * @param ship Ship to remove from the squadron.
    * @return A reference to the updated squadron after removing the ship.
    */
    Squadron& operator-=(Ship& ship);

   /**
    * @brief Adds a ship to the squadron.
    * @param ship Ship to add to the squadron.
    * @return A reference to the updated squadron after adding the ship.
    */
    Squadron& addShip(Ship& ship);

   /**
    * @brief Adds a ship to a copy of the squadron and returns it.
    * @param ship Ship to add to the new squadron.
    * @return New squadron with the ship added.
    */
    Squadron addShip(Ship& ship) const;

   /**
    * @brief Removes the given ship from the squadron if it is a member.
    * @param ship Ship to remove from the squadron.
    * @return A reference to the updated squadron after removing the ship.
    */
    Squadron& removeShip(Ship& ship);

   /**
     * @brief Removes a ship from a copy of the squadron and returns it.
     * @param ship Ship to remove from the new squadron.
     * @return New squadron with the ship removed.
     */
    Squadron removeShip(Ship& ship) const;

   /**
    * @brief Gets the ship at a given index.
    * @param index Index of the ship.
    * @return The ship at the given index.
    * @throws std::out_of_range if the given index is >= to the number of ships in the squadron
     * or if the squadron is empty
    */
    [[nodiscard]] Ship* get(std::size_t index) const;

   /**
    * @brief Gets the name of the squadron.
    * @return The name of the squadron.
    */
    [[nodiscard]] const std::string& getName() const;

   /**
    * @brief Sets the name of the squadron.
    * @param name New name of the squadron.
    */
    void setName(const std::string& name);

   /**
    * @brief Sets the leader ship of the squadron.
    * @note If the leader is not already a member of the squadron, it will be added.
    * @param ship Ship to set as leader.
    */
    void setLeader(Ship& ship);

   /**
    * @brief Gets the leader ship of the squadron.
    * @return The leader ship of the squadron, or nullptr if there is no leader.
    */
    [[nodiscard]] Ship* getLeader() const;

   /**
    * @brief Revokes the leader ship of the squadron, but does not remove it from the squadron.
    */
    void revokeLeader();

   /**
    * @brief Gets the fuel consumption of the squadron for a given distance and speed.
    * @param distance Distance to travel.
    * @param speed Speed of travel.
    * @return The fuel consumption of the squadron.
    * @throws std::invalid_argument If the distance, speed is negative or if the speed exceeds the max speed
    * of a Squadron member.
    */
    [[nodiscard]] double getConsumption(double distance, double speed) const;

   /**
    * @brief Formats the squadron to an output stream.
    * @param os Output stream.
    * @return The formatted output stream.
    */
    std::ostream& formatToStream(std::ostream& os) const;
};


#endif //SQUADRON_HPP
