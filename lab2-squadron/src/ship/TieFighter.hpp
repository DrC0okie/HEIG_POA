/**
 * @class TieFighter
 * @brief Represents a TIE Fighter ship, which is a subclass of Tie.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef TIE_FIGHTER_HPP
#define TIE_FIGHTER_HPP

#include "Ship.hpp"
#include "Tie.hpp"

class TieFighter : public Tie {
private:
    static unsigned id;

public:
   /**
     * @brief Value constructor initializing the TieFighter with a nickname.
     * @param nickName Nickname of the TieFighter ship (default is an empty string).
     */
    explicit TieFighter(const std::string& nickName = "");

   /**
    * @brief Gets the maximum speed of the TieFighter.
    * @return The maximum speed of the TieFighter.
    */
    [[nodiscard]] double getMaxSpeed() const override;

   /**
    * @brief Gets the weight of the TieFighter.
    * @return The weight of the TieFighter.
    */
    [[nodiscard]] double getWeight() const override;

   /**
    * @brief Gets the model of the TieFighter.
    * @return The model of the TieFighter.
    */
    [[nodiscard]] std::string getModel() const override;
};

#endif //TIE_FIGHTER_HPP
