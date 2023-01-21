//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include "../util/Registry.h"
#include "Block.h"

class BlockRegistry : public Registry {
    std::vector<std::reference_wrapper<Block>> blocks;
    std::unordered_map<std::string, std::reference_wrapper<Block>> blocksByKey;

   public:
    explicit BlockRegistry() : Registry("minecraft:block") {}

    void add(Block& block) {
        blocks.emplace_back(block);
        blocksByKey.emplace(block.getName().toString(), block);
    }

    const std::vector<std::reference_wrapper<Block>>& getBlocks() const {
        return blocks;
    }

    const Block& get(int32_t id) const {
        return get(getKey(id));
    }

    const Block& get(const std::string& name) const {
        return blocksByKey.at(name);
    }
};
