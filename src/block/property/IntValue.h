//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include "PropertyValue.h"

class IntValue : public PropertyValue {
    int value;

   public:
    IntValue(int value) : PropertyValue(2), value(value) {} // NOLINT(google-explicit-constructor)

    [[nodiscard]]
    bool equals(const PropertyValue& other) const override {
        return getType() == other.getType() && dynamic_cast<const IntValue&>(other).value == value;
    }

    [[nodiscard]]
    std::string toString() const override {
        return std::to_string(value);
    }
};
