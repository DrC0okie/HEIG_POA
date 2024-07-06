#ifndef POA_LABO4_VAMPIRE_HPP
#define POA_LABO4_VAMPIRE_HPP

#include "Humanoid.hpp"

/**
 * Class representing a vampire
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Vampire : public Humanoid {
public:
    /**
     * Create a new vampire at position
     * @param x x coordinate
     * @param y y coordinate
     */
    Vampire(unsigned x, unsigned y);

    /**
     * Define the next action of a vampire
     * @param field the game field
     */
    void setAction(const Field& field) override;

    /**
     * Return the colored character of a vampire
     * @param os output stream
     * @return the colored character of a vampire
     */
    std::ostream& toStream(std::ostream& os) const override;
};


#endif //POA_LABO4_VAMPIRE_HPP
