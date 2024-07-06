/**
 * @file Bank.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_BANK_H
#define RIVER_BANK_H

#include "Container.h"

/**
 * @class Represents a bank that holds people.
 */
class Bank : public Container {
public:
    /**
     * @brief Construct a new Bank with a given name.
     * @param name The name of the bank.
     */
    explicit Bank(const std::string& name);
};

#endif //RIVER_BANK_H
