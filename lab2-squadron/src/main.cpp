/**
 * @file main.cpp
 * @brief Application for managing squadrons of spaceships, enabling fuel consumption to be calculated, ships to be
 * added or deleted, and squadron details to be displayed. The ships have specific characteristics such as model,
 * speed and cargo capacity. The aim is to simulate the management of space squadrons.
 * @authors Walid Slimani, Timothée Van Hove
 */

#include <iostream>
#include "ship/TieFighter.hpp"
#include "ship/cargo/ImperialShuttle.hpp"
#include "squadron/Squadron.hpp"

using namespace std;

int main() {

    TieFighter blackLeader;
    blackLeader.setNickname("Black leader");
    TieFighter blackTwo;
    ImperialShuttle shuttle(23.4);

    Squadron squad("Black Squadron");
    squad += blackLeader;
    squad += blackTwo;
    squad += shuttle;

    squad.setLeader(blackLeader);

    cout << squad;

    return EXIT_SUCCESS;
}