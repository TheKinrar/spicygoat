//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <memory>
#include <unordered_map>

class Block;

#include <spicygoat/block/Block.h>
#include <spicygoat/block/properties/Property.h>
#include <spicygoat/block/properties/PropertyValue.h>

class BlockState {
    const Block& block;
    const std::unordered_map<int, std::shared_ptr<PropertyValue>> values;

    std::unordered_map<int, std::unordered_map<std::shared_ptr<PropertyValue>, std::shared_ptr<BlockState>>> table;

   public:
    BlockState(const Block& block, const std::unordered_map<int, std::shared_ptr<PropertyValue>>& values);
    BlockState(const std::shared_ptr<BlockState>&) = delete;

    const Block& getBlock() const {
        return block;
    }

    std::shared_ptr<PropertyValue> getValue(const Property& property) {
        return values.at(property.getId());
    }

    [[nodiscard]]
    std::string toString() const;

    std::shared_ptr<BlockState> with(const Property& property, const std::shared_ptr<PropertyValue>& value) const;
    std::shared_ptr<BlockState> with(const Property& property, const std::string& value) const;
    std::shared_ptr<BlockState> with(const std::string& propertyName,
                                     const std::shared_ptr<PropertyValue>& value) const;
    std::shared_ptr<BlockState> with(const std::string& propertyName, const std::string& value) const;

    void load();
};
