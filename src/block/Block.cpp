//
// Created by thekinrar on 19/01/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/block/Block.h>
#include <spicygoat/block/BlockTrait.h>
#include <spicygoat/data/registries.h>

#include <utility>

Block::Block(Identifier name, const std::vector<std::reference_wrapper<const BlockTrait>>& traits,
             const std::vector<std::reference_wrapper<const Property>>& properties,
             const std::vector<std::string>& defaultValues)
    : name(std::move(name)), traits(traits), properties(properties), defaultValues(defaultValues) {
    Server::get().getBlockRegistry().add(*this);
}

void Block::load() {
    std::vector<size_t> indexes;
    indexes.resize(properties.size());

    for(const auto& item : properties) {
        auto& subTable = table[item.get().getId()] = {};
        for(const auto& val : item.get().getValues()) subTable[val] = {};
    }

nextState:
    std::unordered_map<int, std::shared_ptr<PropertyValue>> values;
    if(!properties.empty()) {
        for(int j = 0; j < properties.size(); j++) {
            auto& property = properties.at(j);
            values.emplace(property.get().getId(), property.get().getValues().at(indexes[j]));
        }
    }
    auto state = std::make_shared<BlockState>(*this, values);
    for(const auto& item : values) table[item.first][item.second].push_back(state);
    states.push_back(state);

    for(int j = properties.size() - 1; j >= 0; j--) {
        auto& property = properties.at(j);
        auto i = indexes[j];
        if(i + 1 < property.get().getValues().size()) {
            indexes[j]++;
            goto nextState;
        } else {
            indexes[j] = 0;
        }
    }

    for(auto& state : states) state->load();

    defaultState = states[0];
    for(int i = 0; i < defaultValues.size(); ++i) {
        defaultState = defaultState->with(properties.at(i), defaultValues.at(i));
    }
}

std::shared_ptr<BlockState> Block::getStateToPlace(const BlockPlaceContext& ctx) const {
    auto state = getDefaultState();
    for(const auto& trait : traits) state = trait.get().transformStateToPlace(ctx, state);
    return state;
}
