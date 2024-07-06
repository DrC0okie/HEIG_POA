/**
 * @file Thief.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Thief.h"
#include <algorithm>

Thief::Thief(const std::string& name, const Policeman* p) : Person(name), policeman(p) {
    if (!this->policeman)
        throw std::invalid_argument("Policeman pointer must not be null.");
}

bool Thief::isValid(const Container& c) const {
    // Check if the thief is alone or the policeman is present
    return c.size() == 1 || c.contains(policeman);
}

Status Thief::getDiagnostic() const {
    return Status{true, "Le voleur doit soit etre accompagne par le policer ou etre seul"};
}