/**
 * @file Policeman.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Policeman.h"

Policeman::Policeman(const std::string& name) : Person(name) {}

bool Policeman::canDrive() const {
    return true;
}
