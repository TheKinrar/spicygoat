//
// Created by thekinrar on 16/01/23.
//

#pragma once

#include <string>
#include <utility>
#include <vector>

class BlockState;

#include "../protocol/packets/play/serverbound/PacketUseItemOn.h"
#include "../util/Identifier.h"
#include "../world/geo/Location.h"
#include "BlockState.h"
#include "property/Property.h"

class Block {
    Identifier name;
    std::vector<std::reference_wrapper<const Property>> properties;
    std::vector<std::string> defaultValues;
    std::vector<std::shared_ptr<BlockState>> states;
    std::unordered_map<int, std::unordered_map<std::shared_ptr<PropertyValue>, std::vector<std::shared_ptr<BlockState>>>> table;
    std::shared_ptr<BlockState> defaultState;

   public:
    Block(Identifier name, const std::vector<std::reference_wrapper<const Property>>& properties);
    Block(Identifier name, const std::vector<std::reference_wrapper<const Property>>& properties, const std::vector<std::string>& defaultValues);
    Block(const Block&) = delete;

    void load();

    [[nodiscard]]
    const Identifier& getName() const {
        return name;
    }

    [[nodiscard]]
    const std::vector<std::reference_wrapper<const Property>>& getProperties() const {
        return properties;
    }

    [[nodiscard]]
    const std::shared_ptr<BlockState>& getDefaultState() const {
        return defaultState;
    }

    [[nodiscard]]
    virtual std::shared_ptr<BlockState> getStateToPlace(const Location& loc, const PacketUseItemOn& packet) const {
        return getDefaultState();
    }

    [[nodiscard]]
    const std::vector<std::shared_ptr<BlockState>>& getStates() const {
        return states;
    }

    [[nodiscard]]
    const std::unordered_map<int,
                             std::unordered_map<std::shared_ptr<PropertyValue>,
                                 std::vector<std::shared_ptr<BlockState>>>>& getTable() const {
        return table;
    }

    [[nodiscard]]
    bool isAir() const {
        auto v = name.getValue();
        return v == "air" || v == "cave_air" || v == "void_air";
    }
};
