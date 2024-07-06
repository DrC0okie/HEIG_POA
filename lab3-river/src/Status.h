/**
 * @file Status.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_STATUS_H
#define RIVER_STATUS_H

#include <string>

/**
 * @brief Status structure that contains a boolean error and a string diagnostic
 */
struct Status {
    bool error;
    std::string diagnostic;
};

#endif //RIVER_STATUS_H
