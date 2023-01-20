//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <stdexcept>

#include "BooleanValue.h"
#include "Property.h"

class BooleanProperty : public PropertyTemplate<BooleanValue> {
   public:
    explicit BooleanProperty(const std::string& name)
        : PropertyTemplate(name, PropertyValue::wrap<BooleanValue>({true, false})) {}



//    BooleanValue parse(const std::string& str) override {
//        if(str == "true") return true;
//        else if(str == "false") return false;
//        else throw std::runtime_error("Invalid BooleanProperty value: " + str);
//    }
};
