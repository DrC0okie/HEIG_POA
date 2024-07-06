#include "TieFighter.hpp"

unsigned TieFighter::id{0};

TieFighter::TieFighter(const std::string& nickName) : Tie(nickName) {
    instanceId = ++id;
}

double TieFighter::getMaxSpeed() const {
    return 100;
}

double TieFighter::getWeight() const {
    return 6;
}

std::string TieFighter::getModel() const {
    return Tie::getModel() + "LN";
}
