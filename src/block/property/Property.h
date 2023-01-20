//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "PropertyValue.h"

class Property {
    inline static int nextId = 0;

    const int id;
    const std::string name;

   protected:
    explicit Property(std::string name) : id(nextId++), name(std::move(name)) {}

   public:
    [[nodiscard]]
    int getId() const {
        return id;
    }

    [[nodiscard]]
    const std::string& getName() const {
        return name;
    }

    [[nodiscard]]
    virtual const std::vector<std::shared_ptr<PropertyValue>>& getValues() const = 0;

    [[nodiscard]]
    virtual std::shared_ptr<PropertyValue> parse(std::string str) const = 0;
};

template <class T>
class PropertyTemplate : public Property {
    const std::vector<std::shared_ptr<T>> values;
    std::vector<std::shared_ptr<PropertyValue>> baseValues;
    std::unordered_map<std::string, std::shared_ptr<PropertyValue>> strToValue;

   protected:
    PropertyTemplate(std::string name, std::vector<std::shared_ptr<T>> values)
        : Property(std::move(name)), values(std::move(values)) {
        for(const auto& value : this->values) {
            baseValues.push_back(value);
            strToValue.emplace(value->toString(), value);
        }
    }

   public:
    [[nodiscard]]
    const std::vector<std::shared_ptr<PropertyValue>>& getValues() const override {
        return baseValues;
    }

    [[nodiscard]]
    std::shared_ptr<PropertyValue> parse(std::string str) const override {
        return strToValue.at(str);
    }
};
