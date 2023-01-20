//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <stdexcept>

#include "../../util/stl_util.h"
#include "IntValue.h"
#include "Property.h"

class IntProperty : public PropertyTemplate<IntValue> {
    const int min, max;

   public:
    IntProperty(const std::string& name, int min, int max)
        : PropertyTemplate(name, range(min, max)), min(min), max(max) {}

   private:
    static std::vector<std::shared_ptr<IntValue>> range(int min, int max) {
        std::vector<IntValue> vec;
        for(int i = min; i <= max; ++i) {
            vec.emplace_back(i);
        }
        return PropertyValue::wrap<IntValue>(vec);
    }

//    IntValue parse(const std::string& str) override {
//        int v = std::stoi(str);
//        if(v < min || v > max)
//            throw std::out_of_range("Out of range value for IntProperty: " + std::to_string(v));
//        return v;
//    }
};


