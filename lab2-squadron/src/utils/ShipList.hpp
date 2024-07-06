/**
 * @file ShipList.hpp
 * @brief Header file defining a class for managing a list of ships.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef SHIP_LIST_HPP
#define SHIP_LIST_HPP

#include <ostream>
#include "../ship/Ship.hpp"

class ShipList {
private :
    /**
     * @brief List Node structure
     */
    struct Node;

    /**
     * @class Inner iterator used for parsing the container
     */
    class Iterator {
    public:
       /**
       * @brief Constructor for creating an Iterator object.
       * @param head The head node of the list.
       */
        explicit Iterator(Node* head);

        /**
         * @brief Checks if the iterator is at the end of the list
         * @return true if the iterator is not at the end of the list, false otherwise
         */
        [[nodiscard]] bool hasNext() const;

        /**
         * @brief Get the current value and move the iterator to the next node.
         * @return the Ship of the current node.
         * @throws std::out_of_range if the iterator is at the end of the list
         */
        Ship* next();

    /**
     * @brief Current node of the iterator.
     */
    private:
        Node* current;
    };

    /**
     * @brief Head Node of the list
     */
    Node* head;

    /**
     * @brief Tail Node of the list
     */
    Node* tail;

    /**
     * @brief Exchanges the values of the 2 parameters.
     * @param first first value to be swapped
     * @param second second value to be swapped
     */
    void swap(ShipList& other) noexcept;

public:

    /**
     * @brief default constructor
     */
    ShipList();

    /**
     * @brief Copy constructor
     * @param other Object to copy from
     */
    ShipList(const ShipList& other);

    /**
     * @brief Move constructor
     * @param other Object to move from
     */
    ShipList(ShipList&& other) noexcept;

    /**
     * @brief destructor
     */
    ~ShipList();

    /**
     * @brief Assignment operator that covers both copy and move assignment
     * @details C++11 (and later) will automatically pick the move or copy constructor appropriately.
     * @note https://stackoverflow.com/a/3279550
     * @param other the other object to assign
     * @return a reference to the list
     */
    ShipList& operator=(ShipList other);

    /**
     * @brief Gets the ship at a given index
     * @param index The ship index
     * @return The ship at the given index
     * @throws std::out_of_range if the given index is >= to the number of ships in the list
     * or if the list is empty
     */
    [[nodiscard]] Ship* get(std::size_t index) const;

    /**
     * @brief Adds a ship to the end of the list
     * @param ship The ship to add to the list
     * @throws std::invalid_argument If the given ship is null
     */
    void add(Ship* ship);

    /**
     * @brief Removes the first ship of the list;
     * @param ship The ship to remove
     * @return true if the ship has been removed, false otherwise
     * @throws std::invalid_argument If the given ship is null
     */
    bool remove(Ship* ship);

    /**
     * @brief Clear the list
     */
    void clear();

    /**
     * @brief Checks if the list contains a ship
     * @return True if the list contains the ship, false otherwise
     * @throws std::invalid_argument If the given ship is nullptr
     */
    [[nodiscard]] bool contains(const Ship* ship) const;

    /**
     * @brief Gets a list iterator
     * @return The list iterator
     */
    [[nodiscard]] Iterator getIterator() const;
};

#endif //SHIP_LIST_HPP