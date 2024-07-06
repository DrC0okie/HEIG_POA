#ifndef POA_LABO4_BUFFY_HPP
#define POA_LABO4_BUFFY_HPP

#include "Human.hpp"

/**
 * Class representing Buffy "the vampire slayer"
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Buffy : public Human {
public:
    /**
     * Create a new buffy at position
     * @param x x coordinate
     * @param y y coordinate
     */
    Buffy(unsigned x, unsigned y);

    void setAction(const Field& field) override;

    /**
     * Return the colored character of Buffy
     * @param os output stream
     * @return the colored character of Buffy
     */
    std::ostream& toStream(std::ostream& os) const override;

    /**
     * Buffy cannot be killed
     */
    void kill() override;
};


#endif //POA_LABO4_BUFFY_HPP
