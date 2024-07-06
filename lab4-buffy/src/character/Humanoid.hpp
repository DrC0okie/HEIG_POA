#ifndef POA_LABO4_HUMANOID_HPP
#define POA_LABO4_HUMANOID_HPP

#include <ostream>
#include <memory>
#include "src/Field.hpp"
#include "src/action/Action.hpp"

class Action;

class Field;

/**
 * Class representing an humanoid
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class Humanoid {
private:
    unsigned posX;
    unsigned posY;
    bool alive = true;

protected:
    /**
     * Create an new humanoid at position
     * @param x x coordinate
     * @param y y coordinate
     */
    Humanoid(unsigned x, unsigned y);

    std::shared_ptr<Action> nextAction;

public:
    virtual ~Humanoid() = default;

    /**
     * Define the next action of an humanoid
     * @param field the simulation field
     */
    virtual void setAction(const Field& field) = 0;

    /**
     * Execute the next action of an humanoid
     * @param field the simulation field
     */
    void executeAction(Field& field);

    /**
     * Check if the humanoid is alive of dead
     * @return true if alive, else false
     */
    [[nodiscard]] bool isAlive() const;

    /**
     * Kill the humanoid
     */
    virtual void kill();

    /**
     * Get the humanoid as a output stream
     * @param os output stream
     * @return output stream
     */
    virtual std::ostream& toStream(std::ostream& os) const = 0;

    /**
     * Get the current x coordinate
     * @return x coordinate
     */
    [[nodiscard]] unsigned getX() const;

    /**
    * Get the current y coordinate
    * @return y coordinate
    */
    [[nodiscard]] unsigned getY() const;

    /**
     * Set the current x coordinate
     * @param x x coordinate
     */
    void setX(unsigned x);

    /**
     * Set the current y coordinate
     * @param y y coordinate
     */
    void setY(unsigned y);
};

std::ostream& operator<<(std::ostream& os, const Humanoid& h);

#endif //POA_LABO4_HUMANOID_HPP
