#include "TieInterceptor.hpp"

unsigned TieInterceptor::id{0};

TieInterceptor::TieInterceptor(const std::string& nickName) : Tie(nickName) {
    instanceId = ++id;
}

double TieInterceptor::getMaxSpeed() const {
    return 110;
}

double TieInterceptor::getWeight() const {
    return 5;
}

std::string TieInterceptor::getModel() const {
    return Tie::getModel() + "IN";
}