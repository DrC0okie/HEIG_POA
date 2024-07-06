/**
 * @file Girl.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Girl.h"

Girl::Girl(const std::string& name, const Parent* father, const Parent* mother)
        : Kid(name, mother, father) {}

Status Girl::getDiagnostic() const {
    return Status{true, "Si la fille est avec son pere, sa mere doit aussi etre presente\n"};
}