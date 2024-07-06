/**
 * @file Boy.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_BOY_H
#define RIVER_BOY_H

#include "Kid.h"

/**
 * @brief Class representing the Boy child of 2 Parent instances
 */
class Boy : public Kid {
public:

    /**
     * @brief Construct a Boy with a pointer to his father and mother
     * @param name The name of the boy
     * @param father The pointer to the father
     * @param mother The pointer to the mother
     */
    Boy(const std::string& name, const Parent* father, const Parent* mother);

    [[nodiscard]] Status getDiagnostic() const override;
};

#endif //RIVER_BOY_H
