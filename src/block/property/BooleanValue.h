//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <memory>
#include <vector>

#include "PropertyValue.h"

class BooleanValue : public PropertyValue {
    bool value;

   public:
    BooleanValue(bool value) : PropertyValue(0), value(value) {} // NOLINT(google-explicit-constructor)

    [[nodiscard]]
    bool equals(const PropertyValue& other) const override {
        return getType() == other.getType() && dynamic_cast<const BooleanValue&>(other).value == value;
    }

    [[nodiscard]]
    std::string toString() const override {
        return value ? "true" : "false";
    }
};
