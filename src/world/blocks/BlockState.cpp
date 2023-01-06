//
// Created by thekinrar on 09/04/19.
//

#include "BlockState.h"

#include <cstdint>
#include <utility>

BlockState::BlockState(const std::string &name) : name(name) {}

void BlockState::addProperty(const std::string &key, std::string value) {
    properties[key] = std::move(value);
}

const std::string &BlockState::getName() const {
    return name;
}

bool BlockState::operator<(const BlockState &rhs) const {
    if(name < rhs.name) return true;
    if(rhs.name < name) return false;
    return properties < rhs.properties;
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

std::string BlockState::toString() {
    std::string str;
    str += getName() + "{";

    bool first = true;
    for(auto &property : properties) {
        if(first) {
            first = false;
        } else {
            str += ",";
        }

        str += property.first + "=" + property.second;
    }

    return str + "}";
}
