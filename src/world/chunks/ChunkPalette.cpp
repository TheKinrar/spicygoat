//
// Created by thekinrar on 09/04/19.
//

#include "ChunkPalette.h"

#include <tag_compound.h>
#include <tag_string.h>

#include <cmath>
#include <iostream>

#include "../../Server.h"
#include "../../protocol/PacketData.h"

std::shared_ptr<ChunkPalette> ChunkPalette::fromNBT(nbt::tag_list &list) {
    if(list.size() > 256) return Server::get().getPalette();

    auto palette = std::make_shared<ChunkPalette>();

    for(int i = 0; i < list.size(); ++i) {
        auto &item = list.at(i).as<nbt::tag_compound>();

        auto state = Server::get().getBlockRegistry().get(item.at("Name").as<nbt::tag_string>().get()).getDefaultState();

        if(item.has_key("Properties")) {
            auto props = item.at("Properties").as<nbt::tag_compound>();

            for(auto &prop : props) {
                state = state->with(prop.first, prop.second.as<nbt::tag_string>().get());
            }
        }

        palette->addBlockState(state, i);
    }

    palette->finalize();

    return palette;
}

void ChunkPalette::loadGlobal() {
    global = true;
    int16_t id = 0;
    for(const auto &block : Server::get().getBlockRegistry().getBlocks()) {
        for(const auto &state : block.get().getStates()) {
            addBlockState(state, id++);
        }
    }
}

void ChunkPalette::addBlockState(const std::shared_ptr<BlockState>& state, int16_t id) {
    stateToId[state] = id;
    idToState[id] = state;
}

void ChunkPalette::finalize() {
    bitsPerBlock = ceil(log2(idToState.size()));

    single = bitsPerBlock == 0;

    if(!single && bitsPerBlock < 4) bitsPerBlock = 4;

    global = bitsPerBlock > 8;
}

uint8_t ChunkPalette::getBitsPerBlock() const {
    return bitsPerBlock;
}

void ChunkPalette::writeToByteArray(std::vector<std::byte> &array) {
    PacketData::writeUnsignedByte(bitsPerBlock, array);

    if(single) {
        PacketData::writeVarInt(Server::get().getPalette()->getBlockStateId(idToState.begin()->second), array);
    } else if(!global) {
        PacketData::writeVarInt(idToState.size(), array);

        for(auto &pair : idToState) {
            PacketData::writeVarInt(Server::get().getPalette()->getBlockStateId(pair.second), array);
        }
    }
}

int16_t ChunkPalette::getBlockStateId(const std::shared_ptr<BlockState> &state) const {
    auto it = stateToId.find(state);
    return it == stateToId.end() ? -1 : it->second;
}

std::string ChunkPalette::toString(bool withMapping) {
    return std::string("Palette{g=") + std::to_string(global) + ",len=" + std::to_string(idToState.size()) +
           ",bits=" + std::to_string(bitsPerBlock) + (withMapping ? ",m=\n" + mappingToString() : ",m=...") + "}";
}

std::string ChunkPalette::mappingToString() {
    std::string str;

    for(auto &pair : idToState) {
        str += std::to_string(pair.first) + " -> " + pair.second->toString();

        if(!global)
            str += std::string(" -> ") + std::to_string(Server::get().getPalette()->getBlockStateId(pair.second));

        str += '\n';
    }

    return str;
}
