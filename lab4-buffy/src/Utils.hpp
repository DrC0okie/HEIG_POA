#ifndef POA_LABO4_UTILS_HPP
#define POA_LABO4_UTILS_HPP

#include <cstdlib>

/**
 * Clear the console depending on the OS
 */
inline void clearScreen() {
#if defined _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif //POA_LABO4_UTILS_HPP
