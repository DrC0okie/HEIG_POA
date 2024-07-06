#ifndef LABMATRIX_SUB_H
#define LABMATRIX_SUB_H

#include "../Operator.h"

/**
 * @class Sub
 * @brief Represents a subtraction operator
 * @authors Slimani Walid, Van Hove Timothée
 */
class Sub : public Operator {
public:
   [[nodiscard]] unsigned apply(unsigned n, unsigned m) const override;
};

#endif //LABMATRIX_SUB_H
