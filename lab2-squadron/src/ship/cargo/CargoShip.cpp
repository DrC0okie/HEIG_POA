#include "CargoShip.hpp"
#include <stdexcept>
#include <iomanip>

CargoShip::CargoShip(double baseWeight, double maxLoad, double currentLoad,
                     const std::string& nickName)
        : Ship(nickName), baseWeight(baseWeight), maxLoad(maxLoad) {

    if (baseWeight < 0) {
        throw std::invalid_argument("The base weight must be strictly positive.");
    }

    if (maxLoad < 0) {
        throw std::invalid_argument("The max load must be strictly positive.");
    }

    setLoad(currentLoad);
}

CargoShip::~CargoShip() noexcept = default;

std::ostream& CargoShip::formatToStream(std::ostream& os) const {
    return Ship::formatToStream(os) << "cargo : " << std::fixed << std::setprecision(2)
                                    << currentLoad << " " << "tons" << " (max : " << std::fixed
                                    << std::setprecision(2) << maxLoad << ")";
}

double CargoShip::getWeight() const {
    return baseWeight + currentLoad;
}

void CargoShip::setLoad(double load) {
    if (load < 0) {
        throw std::invalid_argument("The load must be strictly positive.");
    }
    if (load > maxLoad) {
        throw std::invalid_argument("The capacity of this ship does not allow such a heavy load");
    }

    this->currentLoad = load;
}
