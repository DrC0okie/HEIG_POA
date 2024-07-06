/**
 * @file Girl.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_GIRL_H
#define RIVER_GIRL_H

#include "Kid.h"

/**
 * @brief Class representing the Girl child of 2 Parent instances
 */
class Girl : public Kid {
public:

    /**
     * @brief Construct a Girl with a pointer to his father and mother
     * @param name The name of the Girl
     * @param father The pointer to the father
     * @param mother The pointer to the mother
     */
    Girl(const std::string& name, const Parent* father, const Parent* mother);

    [[nodiscard]] Status getDiagnostic() const override;
};

#endif //RIVER_GIRL_H
