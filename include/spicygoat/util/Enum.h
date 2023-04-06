//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Enum {
    std::string _name;

   protected:
    explicit Enum(std::string name) : _name(std::move(name)) {}

   public:
    [[nodiscard]]
    const std::string& name() const {
        return _name;
    }

    template <class T>
    static std::unordered_map<std::string, T> makeMap(std::vector<T> values) {
        std::unordered_map<std::string, T> map;
        for(const auto& item : values) {
            map.emplace(item.name(), item);
        }
        return map;
    }
};
