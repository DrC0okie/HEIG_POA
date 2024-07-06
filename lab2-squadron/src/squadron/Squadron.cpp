#include "Squadron.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <limits>
#include <iomanip>
#include "../constants.hpp"

std::ostream& operator<<(std::ostream& os, const Squadron& squadron) {
    return squadron.formatToStream(os);
}

Squadron operator+(const Squadron& squadron, Ship& ship) {
    return squadron.addShip(ship);
}

Squadron operator+(Ship& ship, const Squadron& squadron) {
    return squadron + ship;
}

Squadron operator-(const Squadron& squadron, Ship& ship) {
    return squadron.removeShip(ship);
}

std::string Squadron::printHeader(const std::string& headerName) {
    return "-- " + headerName + " :";
}

Squadron::Squadron(std::string name) : name(std::move(name)), leader(nullptr), members() {}

Squadron::Squadron(Squadron&& other) noexcept {
    exchange(other);
}

Squadron::~Squadron() {
    revokeLeader();
    members.clear();
}

Squadron::Squadron(const Squadron& other) {
    members.clear();
    copy(other);
}

Squadron& Squadron::operator=(const Squadron& other) {
    if (this != &other) {
        members.clear();
        copy(other);
    }
    return *this;
}

Squadron& Squadron::operator=(Squadron&& other) noexcept {
    if (this != &other) {
        exchange(other);
    }
    return *this;
}

Squadron& Squadron::addShip(Ship& ship) {
    auto it = members.getIterator();
    while (it.hasNext()) {
        if (it.next() == &ship) {
            return *this;
        }
    }
    members.add(&ship);
    return *this;
}

Squadron Squadron::addShip(Ship& ship) const {
    return Squadron(*this).addShip(ship);
}

Squadron& Squadron::removeShip(Ship& ship) {
    if (&ship == leader) {
        revokeLeader();
    }
    members.remove(&ship);
    return *this;
}

Squadron Squadron::removeShip(Ship& ship) const {
    return Squadron(*this).removeShip(ship);
}

Squadron& Squadron::operator+=(Ship& ship) {
    return addShip(ship);
}

const std::string& Squadron::getName() const {
    return name;
}

void Squadron::setName(const std::string& newName) {
    name = newName;
}

void Squadron::setLeader(Ship& ship) {
    addShip(ship);
    leader = &ship;
}


Ship* Squadron::getLeader() const {
    return leader;
}

void Squadron::revokeLeader() {
    leader = nullptr;
}

Squadron& Squadron::operator-=(Ship& ship) {
    return removeShip(ship);
}

Ship* Squadron::get(size_t index) const {
    return members.get(index);
}

double Squadron::getConsumption(double distance, double speed) const {
    double consumption = 0;
    auto it = members.getIterator();
    while (it.hasNext()) {
        const Ship& ship = *it.next();
        consumption += ship.getConsumption(distance, speed);
    }
    return consumption;
}

std::ostream& Squadron::formatToStream(std::ostream& os) const {
    std::stringstream shipsStream;
    auto it = members.getIterator();
    double totalWeight = 0.0, speed = std::numeric_limits<double>::max();

    // get speed, weight and members
    if (it.hasNext()) {
        while (it.hasNext()) {
            auto ship = it.next();
            totalWeight += ship->getWeight();
            speed = std::min(speed, ship->getMaxSpeed());
            if (ship != leader) {
                shipsStream << *ship;
            }
        }
    } else {
        speed = 0.0;
        shipsStream << "None";
    }

    os << "Squadron: " << getName() << std::endl;

    // Print weight
    os << std::setprecision(2) << std::fixed << "total weight : "
       << totalWeight << " " << WEIGHT_UNIT << std::endl;

    // Print speed
    os << std::setprecision(0) << std::fixed << "max speed : "
       << speed << " " << SPEED_UNIT << std::endl;

    // Print leader
    os << printHeader("Leader") << std::endl;

    if (leader != nullptr) {
        os << *leader;
    } else {
        os << "None";
    }

    // Print members
    return os << printHeader("Members") << std::endl << shipsStream.str();
}

void Squadron::exchange(Squadron& other) {
    name = std::exchange(other.name, "");
    members = std::move(other.members);
    leader = std::exchange(other.leader, nullptr);
}

void Squadron::copy(const Squadron& other) {
    name = other.name;
    leader = other.leader;
    members = other.members;
}
