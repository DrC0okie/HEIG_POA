#ifndef LABMATRIX_OPERATOR_H
#define LABMATRIX_OPERATOR_H

/**
 * @brief Abstract class allowing to apply an operation to two numbers.
 * @authors Slimani Walid, Van Hove Timothée
 */
class Operator {
public:
   [[nodiscard]] virtual unsigned apply(unsigned n, unsigned m) const = 0;
};

#endif //LABMATRIX_OPERATOR_H
