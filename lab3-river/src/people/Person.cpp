/**
 * @file Person.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Person.h"
#include <utility>

Person::Person(std::string name) : name(std::move(name)) {}

bool Person::canDrive() const {
    return false;
}

const std::string& Person::getName() const {
    return name;
}

bool Person::isValid([[maybe_unused]]const Container& container) const {
    return true;
}

Status Person::getDiagnostic() const {
    return {false, ""};
}

Person::~Person() = default;
