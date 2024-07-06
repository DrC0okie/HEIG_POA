/**
 * @file Person.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_POLICEMAN_H
#define RIVER_POLICEMAN_H

#include "Person.h"

/**
 * @class Represent a policeman
 */
class Policeman : public Person {
public:
    /**
     * @brief Construct a new Policeman
     * @param name The name of the policeman
     */
    explicit Policeman(const std::string& name);

    [[nodiscard]] bool canDrive() const override;
};

#endif //RIVER_POLICEMAN_H
