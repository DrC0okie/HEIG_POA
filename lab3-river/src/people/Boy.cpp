/**
 * @file Boy.cpp
 * @authors Walid Slimani, Timothée Van Hove
 */

#include "Boy.h"

Boy::Boy(const std::string& name, const Parent* father, const Parent* mother)
        : Kid(name, father, mother) {}

Status Boy::getDiagnostic() const {
    return Status{true, "Si le garcon est avec sa mere, son pere doit aussi etre present\n"};
}