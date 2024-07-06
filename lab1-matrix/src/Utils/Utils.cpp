#include "Utils.h"

unsigned Utils::getRandom(unsigned upperBound) {
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned> distrib(0, upperBound - 1);
    return distrib(gen);
}
