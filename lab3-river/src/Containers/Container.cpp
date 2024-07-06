/**
 * @file Container.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Container.h"
#include <utility>
#include <iostream>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Container& c) {
    return c.toStream(os);
}

Container::Container(std::string name) : name(std::move(name)) {}

void Container::addPerson(personPtr person) {
    if (person != nullptr)
        people.emplace_back(std::move(person));
}

// Transfers the ownership of a person
personPtr Container::removePerson(const std::string& pname) {
    auto it = std::find_if(people.begin(), people.end(), [&](const personPtr& p) {
        return p->getName() == pname;
    });

    if (it != people.end()) {
        personPtr result = std::move(*it); // Move the unique_ptr out of the list
        people.erase(it); // Erase the now-empty unique pointer from the list
        return result;
    }
    // person not found
    return nullptr;
}

bool Container::contains(const Person* person) const {
    return std::any_of(begin(), end(), [person](const personPtr& p) {
        return person == p.get();
    });
}

bool Container::isEmpty() const {
    return people.empty();
}

std::size_t Container::size() const {
    return people.size();
}

void Container::clear() {
    people.clear();
}

const std::string& Container::getName() const {
    return name;
}

std::string Container::toString() const {
    std::ostringstream oss;
    for (const auto& person: people) {
        if (oss.tellp() > 0)
            oss << " ";

        oss << person->getName();
    }
    return oss.str();
}

std::ostream& Container::toStream(std::ostream& os) const {
    os << getName() << ": " << toString();
    return os;
}

Status Container::getStatus() const {
    for (const auto& person: people)
        if (!person->isValid(*this))
            return person->getDiagnostic();

    return Status{false, ""};
}

const_iterator Container::begin() const {
    return people.begin();
}

const_iterator Container::end() const {
    return people.end();
}

Container::~Container() = default;
