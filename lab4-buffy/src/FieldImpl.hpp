#ifndef POA_LABO4_FIELDIMPL_HPP
#define POA_LABO4_FIELDIMPL_HPP

// This file is used to write the definition of templated methods of Field.hpp

#include "src/Field.hpp"

template<class T>
T* Field::getClosestHumanoid(Humanoid* humanoid) const {
    T* closest = nullptr;
    int minDistanceSquared = std::numeric_limits<int>::max();

    for (const auto& h : humanoids) {
        if (!h || h.get() == humanoid)
            continue;

        // Safely use typeid on a dereferenced unique_ptr after confirming it's not nullptr
        if (typeid(*h) != typeid(T))
            continue;

        int dX = static_cast<int>(humanoid->getX()) - static_cast<int>(h->getX());
        int dY = static_cast<int>(humanoid->getY()) - static_cast<int>(h->getY());
        int distanceSquared = dX * dX + dY * dY;

        if (!closest || distanceSquared < minDistanceSquared) {
            closest = dynamic_cast<T*>(h.get());
            minDistanceSquared = distanceSquared;
        }
    }
    return closest;
}

template<class T>
unsigned Field::getHumanoidNb() const {
    unsigned nb = 0;

    for (auto& h: humanoids) {
        if (h && typeid(*h) == typeid(T))
            nb++;
    }
    return nb;
}

#endif //POA_LABO4_FIELDIMPL_HPP
