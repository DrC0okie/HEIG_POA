#ifndef POA_LABO4_TRANSFORM_HPP
#define POA_LABO4_TRANSFORM_HPP

#include "Action.hpp"
#include "src/character/Human.hpp"
#include "Kill.hpp"

/**
 * Class representing a transformation from an Human to a Vampire
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Transform : public Kill {
public:
    /**
     * Prepare a transformation of an human to a vampire
     * @param h human to transform
     */
    explicit Transform(Human* h);

    /**
     * Transform an human to a vampire
     * @param f the simulation field
     */
    void execute(Field& f) override;
};


#endif //POA_LABO4_TRANSFORM_HPP
