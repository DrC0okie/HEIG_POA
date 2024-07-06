#include "StarDreadnought.hpp"

unsigned StarDreadnought::id{0};

StarDreadnought::StarDreadnought(double currentLoad, const std::string& nickName)
        : CargoShip(9e9, 250'000, currentLoad, nickName) {
    instanceId = ++id;
}

double StarDreadnought::getMaxSpeed() const {
    return 40;
}

std::string StarDreadnought::getModel() const {
    return "Super-class Star Destroyer";
}