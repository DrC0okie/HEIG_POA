#ifndef LABMATRIX_ADD_H
#define LABMATRIX_ADD_H

#include "../Operator.h"

/**
 * @class Add
 * @brief Represents an addition operator
 * @authors Slimani Walid, Van Hove Timothée
 */
class Add : public Operator {
public:
   [[nodiscard]] unsigned apply(unsigned n, unsigned m) const override;
};

#endif //LABMATRIX_ADD_H
