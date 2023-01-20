//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <unordered_map>

#include "../../util/Enum.h"
#include "../../util/stl_util.h"
#include "Property.h"
#include "EnumValue.h"

template <class T>
class EnumProperty : public PropertyTemplate<EnumValue<T>> {
//    const std::unordered_map<std::string, T> valuesMap;

   public:
    EnumProperty(const std::string& name, const std::vector<T>& values)
        : PropertyTemplate<EnumValue<T>>(name, wrap(values)) {}

   private:
    static std::vector<std::shared_ptr<EnumValue<T>>> wrap(const std::vector<T>& values) {
        std::vector<EnumValue<T>> vec;
        for(const auto& item : values)
            vec.push_back(item);
        return PropertyValue::wrap<EnumValue<T>>(vec);
    }

//    EnumValue<T> parse(const std::string& str) override {
//        return valuesMap.at(str);
//    }
};
