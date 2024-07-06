/**
 * @file ControllerConstants.h
 * @authors Walid Slimani, Timothée Van Hove
 * @brief Constants used by the Controller class.
 */

#ifndef RIVER_CONTROLLERCONSTANTS_H
#define RIVER_CONTROLLERCONSTANTS_H

#include <string>

static const int WIDTH = 58;
static const int BOAT_CAPACITY = 2;
static const char DISPLAY = 'p';
static const char EMBARK = 'e';
static const char DISEMBARK = 'd';
static const char MOVE = 'm';
static const char RESET = 'r';
static const char QUIT = 'q';
static const char MENU = 'h';
static const std::string PROBLEM_SOLVED = "Probleme resolu !";
static const std::string INVALID_COMMAND = "Commande invalide !";
static const std::string BOAT_FULL = "Le bateau est plein !";
static const std::string BOAT_WITHOUT_DRIVER = "Le bateau a besoin d'un chauffeur pour bouger";
static const std::string NOT_PRESENT = " n'est pas present(e)";
static const std::string BOAT_NAME = "Bateau";
static const std::string GAME_END = "Partie terminee";

#endif //RIVER_CONTROLLERCONSTANTS_H
