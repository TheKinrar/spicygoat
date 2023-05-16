//
// Created by thekinrar on 16/01/23.
//

#pragma once

#include <string>
#include <utility>

class Identifier {
    std::string ns = "minecraft";
    std::string val;

   public:
    Identifier(std::string val) : val(std::move(val)) {}  // NOLINT(google-explicit-constructor)

    [[nodiscard]]
    const std::string& getNamespace() const {
        return ns;
    }

    [[nodiscard]]
    const std::string& getValue() const {
        return val;
    }

    [[nodiscard]]
    std::string toString() const {
        return ns + ":" + val;
    }
};
