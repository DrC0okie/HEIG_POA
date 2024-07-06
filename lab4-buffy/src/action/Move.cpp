#include "Move.hpp"

Move::Move(Humanoid* h, unsigned x, unsigned y) : Action(h), toX(x), toY(y) {}

void Move::execute(Field& f) {
    target->setX(toX);
    target->setY(toY);
}
