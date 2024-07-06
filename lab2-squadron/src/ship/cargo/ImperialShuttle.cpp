#include "ImperialShuttle.hpp"

unsigned ImperialShuttle::id{0};

ImperialShuttle::ImperialShuttle(double currentLoad, const std::string& nickName)
        : CargoShip(360, 80, currentLoad, nickName) {
    instanceId = ++id;
}

double ImperialShuttle::getMaxSpeed() const {
    return 54;
}

std::string ImperialShuttle::getModel() const {
    return "Lambda-class shuttle";
}