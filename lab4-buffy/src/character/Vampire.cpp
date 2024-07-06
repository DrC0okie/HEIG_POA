#include <random>
#include "Vampire.hpp"
#include "Human.hpp"
#include "src/action/Move.hpp"
#include "src/action/Kill.hpp"
#include "src/action/Transform.hpp"
#include "src/FieldImpl.hpp"

void Vampire::setAction(const Field& field) {
    auto* closestHuman = field.getClosestHumanoid<Human>(this);

    if (closestHuman == nullptr)
        return;

    const int speed = 1;
    int deltaX = static_cast<int>(closestHuman->getX()) - static_cast<int>(getX());
    int deltaY = static_cast<int>(closestHuman->getY()) - static_cast<int>(getY());

    if (std::abs(deltaX) <= 1 && std::abs(deltaY) <= 1) {
        if (std::bernoulli_distribution(0.5)(field.getRandomEngine()))
            nextAction = std::make_shared<Kill>(closestHuman);

        else
            nextAction = std::make_shared<Transform>(closestHuman);
    }
    else {
        nextAction = std::make_shared<Move>(
                this,
                getX() + std::min(std::max(deltaX, -speed), speed),
                getY() + std::min(std::max(deltaY, -speed), speed)
        );
    }
}

std::ostream& Vampire::toStream(std::ostream& os) const {
    return os << "\033[1;31mV\033[0m";
}

Vampire::Vampire(unsigned int x, unsigned int y) : Humanoid(x, y) {}