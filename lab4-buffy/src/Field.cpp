#include <iostream>
#include <random>
#include <chrono>
#include "src/Field.hpp"
#include "src/character/Buffy.hpp"
#include "src/character/Vampire.hpp"

Field::Field(unsigned int height, unsigned int width, unsigned int nbHumans, unsigned int nbVampires) :
        height(height),
        width(width),
        nbHumans(nbHumans),
        nbVampires(nbVampires) {

    std::random_device rd;
    engine.seed(rd());

    std::uniform_int_distribution<unsigned> widthDist(0, height - 1);
    std::uniform_int_distribution<unsigned> heightDist(0, width - 1);

    add(std::make_unique<Buffy>(widthDist(engine), heightDist(engine)));

    for (size_t i = 0; i < nbHumans; ++i)
        add(std::make_unique<Human>(widthDist(engine), heightDist(engine)));

    for (size_t i = 0; i < nbVampires; ++i)
        add(std::make_unique<Vampire>(widthDist(engine), heightDist(engine)));
}

Field::~Field() = default;

void Field::add(std::unique_ptr<Humanoid> h) {
    humanoids.push_back(std::move(h));
}

unsigned Field::nextTurn() {

    for (auto & humanoid : humanoids)
        humanoid->setAction(*this);

    for (auto & humanoid : humanoids)
        humanoid->executeAction(*this);

    auto it = humanoids.begin();
    while (it != humanoids.end()) {
        if (!(*it)->isAlive()) {
            it = humanoids.erase(it);  // Automatically deletes the humanoid
        } else {
            ++it;
        }
    }
    return ++turn;
}

unsigned Field::getHeight() const {
    return height;
}

unsigned Field::getWidth() const {
    return width;
}

unsigned Field::getNbHumans() const {
    return nbHumans;
}

unsigned Field::getNbVampires() const {
    return nbVampires;
}

std::vector<Humanoid*> Field::getHumanoid2DVector() const {

    std::vector<Humanoid*> array(height * width, nullptr);
    for (const auto& humanoid : humanoids) {
        auto x = humanoid->getX();
        auto y = humanoid->getY();

        if (x < width && y < height) {
            // Calculate the index in the flattened vector
            unsigned index = x + y * width;
            array[index] = humanoid.get();
        }
    }
    return array;
}


unsigned Field::getTurn() const {
    return turn;
}

std::mt19937& Field::getRandomEngine() const {
    return engine;
}