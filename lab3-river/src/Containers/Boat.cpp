/**
 * @file Boat.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Boat.h"
#include <memory>

Boat::Boat(const std::string& name, std::size_t capacity)
        : Container(name), capacity(capacity) {}

bool Boat::isFull() const {
    return size() >= capacity;
}

bool Boat::hasDriver() const {
    return std::any_of(begin(), end(), [](const personPtr& person) {
        return person->canDrive();
    });
}

void Boat::dockAt(const std::shared_ptr<Bank>& bank) {
    // Store a weak reference to the bank
    dockedBank = bank;
}

bool Boat::isDockedAt(const Bank& bank) const {
    // Try to get a shared_ptr from weak_ptr
    auto sp = dockedBank.lock();
    return sp && (sp.get() == &bank);
}

std::ostream& Boat::toStream(std::ostream& os) const {
    os << getName() << ": <";
    if (!isEmpty())
        os << toString();

    os << ">";
    return os;
}
