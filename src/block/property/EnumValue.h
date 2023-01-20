//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <memory>
#include <vector>

#include "PropertyValue.h"

template <class T>
class EnumValue : public PropertyValue {
    T value;

   public:
    EnumValue(T value) : PropertyValue(1), value(value) {} // NOLINT(google-explicit-constructor)

    [[nodiscard]]
    bool equals(const PropertyValue& other) const override {
        return getType() == other.getType() && dynamic_cast<const EnumValue&>(other).value.name() == value.name();
    }

    [[nodiscard]]
    std::string toString() const override {
        return value.name();
    }
};
