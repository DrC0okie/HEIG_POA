/**
 * @file Parent.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Parent.h"

Parent::Parent(const std::string& name) : Person(name) {}

bool Parent::canDrive() const {
    return true;
}