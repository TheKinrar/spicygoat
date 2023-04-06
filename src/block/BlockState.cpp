//
// Created by thekinrar on 19/01/23.
//

#include <iostream>

#include <spicygoat/block/BlockState.h>

BlockState::BlockState(
    const Block& block,
    const std::unordered_map<int, std::shared_ptr<PropertyValue>>& values)
    : block(block), values(values) {}

void BlockState::load() {
    for(const auto& property : block.getProperties()) {
        table[property.get().getId()] = {};

        for(const auto& value : property.get().getValues()) {
            auto targetValues = values;
            targetValues[property.get().getId()] = value;

            for(const auto& other : block.getTable().at(property.get().getId()).at(value)) {
                bool equal = true;
                for(const auto& property : block.getProperties()) {
                    if(!other->values.at(property.get().getId())->equals(*targetValues.at(property.get().getId()))) {
                        equal = false;
                        break;
                    }
                }

                if(equal) {
                    table[property.get().getId()][value] = other;
                    break;
                }
            }
        }
    }
}

std::shared_ptr<BlockState> BlockState::with(const Property& property, const std::shared_ptr<PropertyValue>& value) const {
    return table.at(property.getId()).at(value);
}

std::shared_ptr<BlockState> BlockState::with(const Property& property, const std::string& value) const {
    return table.at(property.getId()).at(property.parse(value));
}

std::shared_ptr<BlockState> BlockState::with(const std::string& propertyName,
                                             const std::shared_ptr<PropertyValue>& value) const {
    for(const auto& item : block.getProperties()) {
        if(item.get().getName() == propertyName) {
            return with(item, value);
        }
    }

    throw std::out_of_range("Unknown property");
}

std::shared_ptr<BlockState> BlockState::with(const std::string& propertyName, const std::string& value) const {
    for(const auto& item : block.getProperties()) {
        if(item.get().getName() == propertyName) {
            return with(item, item.get().parse(value));
        }
    }

    throw std::out_of_range("Unknown property");
}

std::string BlockState::toString() const {
    auto str = block.getName().toString();
    if(!block.getProperties().empty()) {
        str += "[";
        bool first = true;
        for(const auto& property : block.getProperties()) {
            if(first) first = false;
            else str += ",";
            str += property.get().getName() + "=" + values.at(property.get().getId())->toString();
        }
        str += "]";
    }
    return str;
}
