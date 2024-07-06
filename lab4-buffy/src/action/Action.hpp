#ifndef POA_LABO4_ACTION_HPP
#define POA_LABO4_ACTION_HPP

#include "src/Field.hpp"

class Field;
class Humanoid;

/**
 * Class representing a simulation action, performed on an humanoid
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Action {
protected:
    /**
     * Prepare an action on a target humanoid
     * @param humanoid target humanoid
     */
    explicit Action(Humanoid* humanoid);

    Humanoid* target;

public:
    /**
     * Execute the action
     * @param f the simulation field
     */
    virtual void execute(Field& f) = 0;

    virtual ~Action() = default;
};


#endif //POA_LABO4_ACTION_HPP
