/**
 * @file Person.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_PERSON_H
#define RIVER_PERSON_H

#include <string>
#include "../Status.h"
#include "../Containers/Container.h"

class Container;

/**
 * @brief Class representing a person
 */
class Person {
public :

    /**
     * @brief Construct a Person with its name
     * @param name The name of the person
     */
    explicit Person(std::string name);

    /**
     * @brief Check if the person can drive
     * @return true if the person can drive, false otherwise
     */
    [[nodiscard]] virtual bool canDrive() const;

    /**
     * @brief Get the name of the person
     * @return The name of the person
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * @brief Check if the person is valid in a given container context
     * @param container The container to check the person in
     * @return true if the person is valid in the container context, false otherwise
     */
    [[nodiscard]] virtual bool isValid(const Container& c) const;

    /**
     * @brief Get the diagnostic of a potentially violated rule for the person
     * @return The Status structure containing the error state and the diagnostic message
     */
    [[nodiscard]] virtual Status getDiagnostic() const;

    /**
     * Destructor
     */
    virtual ~Person();

private:
    std::string name;
};


#endif //RIVER_PERSON_H
