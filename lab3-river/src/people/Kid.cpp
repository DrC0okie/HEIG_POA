/**
 * @file Kid.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include <algorithm>
#include "Kid.h"

Kid::Kid(const std::string& name, const Parent* dependsOn, const Parent* cantStayWith)
        : Person(name), dependsOn(dependsOn), cantStayWith(cantStayWith) {
    if (!this->dependsOn || !this->cantStayWith)
        throw std::invalid_argument("Parent pointers must not be null.");
}

bool Kid::isValid(const Container& c) const {
    return !c.contains(cantStayWith) || c.contains(dependsOn);
}

Kid::~Kid() = default;