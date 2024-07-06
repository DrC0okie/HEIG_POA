/**
 * @file Container.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_CONTAINER_H
#define RIVER_CONTAINER_H

#include <list>
#include <string>
#include <memory>
#include <functional>
#include "../people/Person.h"
#include "../Status.h"

class Person;
class Container;

/**
 * @brief Outputs the container representation to a stream.
 * @param os The output stream.
 * @param container The container to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Container& container);

// Define types for convenience
using personPtr = std::unique_ptr<const Person>;
using const_iterator = std::list<personPtr>::const_iterator;

/**
 * @class Manages a list of people, providing functionalities to add, remove, and query people.
 */
class Container {
public:
    /**
     * @brief Construct a new Container with a given name.
     * @param name The name of the container.
     */
    explicit Container(std::string name);

    /**
     * @brief Adds a person to the container.
     * @param person Unique pointer to the person being added.
     */
    void addPerson(personPtr person);

    /**
     * @brief Removes a person by name from the container.
     * @param name The name of the person to remove.
     * @return A unique pointer to the removed person, or nullptr if not found.
     */
    [[nodiscard]] personPtr removePerson(const std::string& name);

    /**
     * @brief Indicates if the container contains a given person.
     * @param person The person to check for.
     * @return True if the container contains the person, false otherwise.
     */
    [[nodiscard]] bool contains(const Person* person) const;

    /**
     * @brief Checks if the container is empty.
     * @return True if the container is empty, false otherwise.
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Gets the number of people in the container.
     * @return The number of people in the container.
     */
    [[nodiscard]] size_t size() const;

    /**
     * @brief Clears the container of all people.
     */
    void clear();

    /**
     * @brief Gets the name of the container.
     * @return The name of the container.
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * @brief Gets the status of the container.
     * @return The status of the container.
     */
    [[nodiscard]] Status getStatus() const;

    /**
      * @brief Returns a constant iterator pointing to the beginning of the container.
      * @return Constant iterator to the beginning.
      */
    [[nodiscard]] const_iterator begin() const;

    /**
     * @brief Returns a constant iterator pointing to the end of the container.
     * @return Constant iterator to the end.
     */
    [[nodiscard]] const_iterator end() const;

    /**
     * @brief Outputs the container to a stream.
     * @param os The output stream.
     * @return The output stream.
     */
    virtual std::ostream& toStream(std::ostream& os) const;

    /**
     * @brief Destructor for Container.
     */
    virtual ~Container();

protected:
    /**
     * @brief Returns a string representing all people in the container.
     * @return A string listing all people by name, separated by spaces.
     */
    [[nodiscard]] std::string toString() const;

private:
    std::string name;
    std::list<personPtr> people;
};

#endif //RIVER_CONTAINER_H
