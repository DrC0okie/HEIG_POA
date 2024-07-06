/**
 * @file Boat.h
 * @authors Walid Slimani, Timothée Van Hove
 */
#ifndef RIVER_BOAT_H
#define RIVER_BOAT_H

#include "Container.h"
#include "Bank.h"
#include <memory>

/**
 * @class Represents a boat that hold people to be carried across the river.
 */
class Boat : public Container {
public:

    /**
     * @brief Construct a new Boat with a given name and capacity.
     * @param name The name of the boat.
     * @param capacity The maximum number of people the boat can hold.
     */
    explicit Boat(const std::string& name, std::size_t capacity);

    /**
     * @brief Checks if the boat is full.
     * @return True if the boat is full, false otherwise.
     */
    [[nodiscard]] bool isFull() const;

    /**
     * @brief Checks if the boat has a driver.
     * @return True if the boat has a driver, false otherwise.
     */
    [[nodiscard]] bool hasDriver() const;

    /**
     * @brief Docks the boat at a bank.
     * @param bank The bank to dock at.
     */
    void dockAt(const std::shared_ptr<Bank>& bank);

    /**
     * @brief Checks if the boat is docked at a bank.
     * @param bank The bank to check.
     * @return True if the boat is docked at the bank, false otherwise.
     */
    [[nodiscard]] bool isDockedAt(const Bank& bank) const;

    /**
     * @brief Outputs the boat representation to a stream.
     * @param os The output stream.
     * @return The output stream.
     */
    std::ostream& toStream(std::ostream& os) const override;

private:
    std::size_t capacity;
    std::weak_ptr<Bank> dockedBank;
};

#endif //RIVER_BOAT_H
