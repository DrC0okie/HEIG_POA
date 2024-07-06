/**
 * @file TieInterceptor.hpp
 * @brief Header file defining the TieInterceptor class, a subclass of Tie representing a TIE Interceptor ship.
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef TIE_INTERCEPTOR_HPP
#define TIE_INTERCEPTOR_HPP

#include "Ship.hpp"
#include "Tie.hpp"

class TieInterceptor : public Tie {
private:
    static unsigned id;

public:
   /**
     * @brief Value constructor initializing the TieInterceptor with a nickname.
     * @param nickName Nickname of the TieInterceptor ship (default is an empty string).
     */
    explicit TieInterceptor(const std::string& nickName = "");

   /**
    * @brief Gets the maximum speed of the TieInterceptor.
    * @return The maximum speed of the TieInterceptor.
    */
    [[nodiscard]] double getMaxSpeed() const override;

   /**
    * @brief Gets the weight of the TieInterceptor.
    * @return The weight of the TieInterceptor.
    */
    [[nodiscard]] double getWeight() const override;

   /**
    * @brief Gets the model of the TieInterceptor.
    * @return The model of the TieInterceptor.
    */
    [[nodiscard]] std::string getModel() const override;
};

#endif //TIE_INTERCEPTOR_HPP
