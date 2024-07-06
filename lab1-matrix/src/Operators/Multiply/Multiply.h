#ifndef LABMATRIX_MULTIPLY_H
#define LABMATRIX_MULTIPLY_H

#include "../Operator.h"

/**
 * @class Multiply
 * @brief Represents a multiplication operator
 * @authors Slimani Walid, Van Hove Timothée
 */
class Multiply : public Operator {
public:
   [[nodiscard]] unsigned apply(unsigned n, unsigned m) const override;
};

#endif //LABMATRIX_MULTIPLY_H
