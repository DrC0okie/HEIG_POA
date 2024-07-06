#include <iostream>
#include "Humanoid.hpp"

Humanoid::Humanoid(unsigned x, unsigned y) : posX(x), posY(y), nextAction(nullptr) {}

void Humanoid::setX(unsigned int x) {
    posX = x;
}

void Humanoid::setY(unsigned int y) {
    posY = y;
}

unsigned Humanoid::getX() const {
    return posX;
}

unsigned Humanoid::getY() const {
    return posY;
}

void Humanoid::executeAction(Field& field) {
    if (nextAction != nullptr) {
        nextAction->execute(field);
        nextAction.reset();
    }
}

bool Humanoid::isAlive() const {
    return alive;
}

void Humanoid::kill() {
    alive = false;
}

std::ostream& operator<<(std::ostream& os, const Humanoid& h) {
    return h.toStream(os);
}

