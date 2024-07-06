#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <utility>
#include "Ship.hpp"
#include "../constants.hpp"

std::ostream& operator<<(std::ostream& os, const Ship& ship) {
    return ship.formatToStream(os);
}

Ship::Ship(std::string nickname) : nickname(std::move(nickname)) {}

Ship::~Ship() noexcept = default;

void Ship::setNickname(const std::string& name) {
    nickname = name;
}

std::string Ship::getNickname() const {
    return nickname;
}

double Ship::getId() const {
    return instanceId;
}

double Ship::getConsumption(double distance, double speed) const {
    if (distance < 0 || speed < 0){
        throw std::invalid_argument("Distance and speed must be strictly positive.");
    }
    if (speed > getMaxSpeed()) {
        throw std::invalid_argument("The ship does not support such a high speed.");
    }

    return cbrt(getWeight()) / 2 * log10(getWeight() * speed) * log10(distance + 1);
}

std::ostream& Ship::formatToStream(std::ostream& os) const {
    return os << std::fixed << (nickname.empty() ? "" : nickname + " ") << "[" << getModel() << " #"
              << instanceId << "]" << std::endl << std::setprecision(2) << "weight : "
              << getWeight() << " " << WEIGHT_UNIT << std::endl << std::setprecision(0)
              << "speed : " << getMaxSpeed() << " " << SPEED_UNIT << std::endl;
}
