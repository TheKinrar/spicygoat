//
// Created by thekinrar on 15/01/23.
//

#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

class Tag {
    std::string name;
    std::vector<int> targets;

   public:
    explicit Tag(std::string  name, std::vector<int> targets) : name(std::move(name)), targets(std::move(targets)) {}

    [[nodiscard]]
    const std::string& getName() const {
        return name;
    }

    [[nodiscard]]
    const std::vector<int>& getTargets() const {
        return targets;
    }
};
