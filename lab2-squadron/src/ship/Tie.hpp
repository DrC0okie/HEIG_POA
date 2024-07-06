/**
 * @file Tie.hpp
 * @brief Header file defining the Tie class, a subclass of Ship representing a TIE ship.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef TIE_HPP
#define TIE_HPP

#include "Ship.hpp"

class Tie : public Ship {
protected:
    /**
      * @brief Value constructor initializing the Tie with a nickname.
      * @param nickName Nickname of the Tie ship.
      */
    explicit Tie(const std::string& nickName);

public:

    /**
     * @brief Destructor of the Tie ship.
     */
    ~Tie() noexcept override;

    /**
      * @brief Gets the model of the Tie ship.
      * @return The model of the Tie ship.
      */
    [[nodiscard]] std::string getModel() const override;
};

#endif //TIE_HPP
