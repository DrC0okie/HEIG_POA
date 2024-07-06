#include "Transform.hpp"
#include "src/character/Vampire.hpp"

Transform::Transform(Human* h) : Kill(h) {}

void Transform::execute(Field& f) {
    if (target->isAlive())
        f.add(std::make_unique<Vampire>(target->getX(), target->getY()));

    Kill::execute(f);
}
