//
// Created by thekinrar on 09/04/19.
//

#ifndef SPICYGOAT_BLOCKSTATE_H
#define SPICYGOAT_BLOCKSTATE_H

#include <cstdint>
#include <map>
#include <string>

class BlockState {
   public:
    BlockState() = default;
    explicit BlockState(const std::string &name);
    explicit BlockState(std::string name, std::map<std::string, std::string> properties) :
          name(std::move(name)), properties(std::move(properties)) {};

    void addProperty(const std::string &key, std::string value);

    [[nodiscard]]
    const std::string &getName() const;

    [[nodiscard]] bool isAir() const {
        return name == "minecraft:air" || name == "minecraft:cave_air" || name == "minecraft:void_air";
    }

    bool operator<(const BlockState &rhs) const;

    bool operator>(const BlockState &rhs) const;

    bool operator<=(const BlockState &rhs) const;

    bool operator>=(const BlockState &rhs) const;

    std::string toString();

   private:
    std::string name;

    std::map<std::string, std::string> properties;
};

#endif  // SPICYGOAT_BLOCKSTATE_H
