/**
 * @file Thief.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_THIEF_H
#define RIVER_THIEF_H

#include "Policeman.h"
#include "../Containers/Container.h"

/**
 * @class Represent a thief that is constrained to a policeman
 */
class Thief : public Person {
public :
    /**
     * @brief Construct a new Thief with its name and the policeman it is constrained to
     * @param name The name of the thief
     * @param policeman The policeman pointer the thief is constrained to
     */
    Thief(const std::string& name, const Policeman* p);

    [[nodiscard]] bool isValid(const Container& c) const override;

    [[nodiscard]] Status getDiagnostic() const override;

private:
    const Policeman* policeman;
};

#endif //RIVER_THIEF_H
