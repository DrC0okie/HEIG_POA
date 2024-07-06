#include <iostream>
#include <random>
#include "Human.hpp"
#include "src/action/Move.hpp"

void Human::setAction(const Field& field) {
    //create a vector with all possible moves
    std::vector<std::pair<unsigned, unsigned>> possibleMoves;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            int newX = static_cast<int>(getX()) + dx;
            int newY = static_cast<int>(getY()) + dy;

            if (newX >= 0 && newX < field.getWidth() && newY >= 0 && newY < field.getHeight()) {
                possibleMoves.emplace_back(newX, newY);
            }
        }
    }

    //randomly select a move
    if (!possibleMoves.empty()) {
        std::uniform_int_distribution<size_t> dist(0, possibleMoves.size() - 1);
        size_t randomIndex = dist(field.getRandomEngine());
        nextAction = std::make_shared<Move>(this, possibleMoves[randomIndex].first, possibleMoves[randomIndex].second);
    }
}

std::ostream& Human::toStream(std::ostream& os) const {
    return os << "\033[1;36mH\033[0m";
}

Human::Human(unsigned int x, unsigned int y) : Humanoid(x, y) {}
