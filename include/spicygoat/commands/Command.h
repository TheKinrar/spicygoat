//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <string>
#include <utility>

#include <spicygoat/entities/types/EntityPlayer.h>

class Command {
    std::string name;

   public:
    explicit Command(std::string  name) : name(std::move(name)) {}
    virtual ~Command() = default;

    [[nodiscard]] const std::string& getName() const {
        return name;
    }

    virtual void run(const std::vector<std::string>& args, EntityPlayer& sender) = 0;
};
