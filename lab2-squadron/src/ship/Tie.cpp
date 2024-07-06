#include "Tie.hpp"

Tie::Tie(const std::string& nickName) : Ship(nickName) {}

std::string Tie::getModel() const {
    return "TIE/";
}

Tie::~Tie() noexcept = default;
