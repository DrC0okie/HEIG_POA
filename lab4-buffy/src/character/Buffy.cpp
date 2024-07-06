#include <iostream>
#include "Buffy.hpp"
#include "Vampire.hpp"
#include "src/action/Kill.hpp"
#include "src/action/Move.hpp"
#include "src/FieldImpl.hpp"

void Buffy::setAction(const Field& field) {
    auto* vampire  = field.getClosestHumanoid<Vampire>(this);

    if (vampire  == nullptr) {
        Human::setAction(field);
        return;
    }

    const int speed = 2;
    int deltaX = static_cast<int>(vampire->getX()) - static_cast<int>(getX());
    int deltaY = static_cast<int>(vampire->getY()) - static_cast<int>(getY());

    if (abs(deltaX) <= 1 && abs(deltaY) <= 1)
        nextAction = std::make_shared<Kill>(vampire);

    else {
        nextAction = std::make_shared<Move>(
                this,
                getX() + std::min(std::max(deltaX, -speed), speed),
                getY() + std::min(std::max(deltaY, -speed), speed)
        );
    }
}

std::ostream& Buffy::toStream(std::ostream& os) const {
    return os << "\033[1;32mB\033[0m";
}

Buffy::Buffy(unsigned int x, unsigned int y) : Human(x, y) {}

void Buffy::kill() {}
