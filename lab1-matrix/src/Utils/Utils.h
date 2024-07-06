#ifndef LABMATRIX_UTILS_H
#define LABMATRIX_UTILS_H

#include <random>

/**
 * @class Utils
 * @brief Helper class that contains helper methods used within the matrix classes
 * @authors Slimani Walid, Van Hove Timothée
 */
class Utils {
public:

    /**
     * Returns a random generated unsigned number
     * @param upperBound the upper bound of the distribution used to generate the number
     * @return a random generated unsigned number
     */
    static unsigned getRandom(unsigned upperBound);
};

#endif //LABMATRIX_UTILS_H
