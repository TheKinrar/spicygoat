//
// Created by thekinrar on 14/03/23.
//

#pragma once

#include <string>
#include <utility>

class Plugin {
    std::string id;

   public:
    explicit Plugin(std::string id) : id(std::move(id)) {}

    [[nodiscard]]
    const std::string& getId() const {
        return id;
    }
};
