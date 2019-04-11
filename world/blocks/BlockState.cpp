//
// Created by thekinrar on 09/04/19.
//

#include <cstdint>
#include "BlockState.h"

BlockState::BlockState(const std::string &name) : name(name) {}

bool BlockState::operator<(const BlockState &rhs) const {
    return name < rhs.name;
}

bool BlockState::operator>(const BlockState &rhs) const {
    return rhs < *this;
}

bool BlockState::operator<=(const BlockState &rhs) const {
    return !(rhs < *this);
}

bool BlockState::operator>=(const BlockState &rhs) const {
    return !(*this < rhs);
}

const std::string &BlockState::getName() const {
    return name;
}
