#ifndef POA_LABO4_MOVE_HPP
#define POA_LABO4_MOVE_HPP

#include "Action.hpp"
#include "src/character/Humanoid.hpp"

/**
 * Class representing a move of an humanoid
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Move : public Action {
private:
    const unsigned toX;
    const unsigned toY;

public:
    /**
     * Prepare a move of an humanoid
     * @param h humanoid to move
     * @param x x coordinate of move
     * @param y y coordinate of move
     */
    Move(Humanoid* h, unsigned x, unsigned y);

    /**
     * Move the humanoid
     * @param f the simulation field
     */
    void execute(Field& f) override;
};


#endif //POA_LABO4_MOVE_HPP
