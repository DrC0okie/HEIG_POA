/**
 * @file Parent.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_PARENT_H
#define RIVER_PARENT_H

#include "Person.h"

/**
 * @class Represent a father or a mother of a family
 */
class Parent : public Person {
public:

    /**
     * @brief Construct a new Parent
     * @param name The name of the parent
     */
    explicit Parent(const std::string& name);

    [[nodiscard]] bool canDrive() const override;
};

#endif //RIVER_PARENT_H
