//
// Created by thekinrar on 09/04/19.
//

#include "ChunkPalette.h"
#include "../../protocol/PacketData.h"
#include "../../Server.h"
#include <tag_compound.h>
#include <tag_string.h>
#include <cmath>
#include <iostream>

ChunkPalette *ChunkPalette::fromNBT(nbt::tag_list &list) {
    if (list.size() > 256)
        return Server::get()->getPalette();

    auto palette = new ChunkPalette();

    for (int i = 0; i < list.size(); ++i) {
        auto &item = list.at(i).as<nbt::tag_compound>();

        auto state = new BlockState(item.at("Name").as<nbt::tag_string>().get());

        if (item.has_key("Properties")) {
            auto props = item.at("Properties").as<nbt::tag_compound>();

            for (auto &prop : props) {
                state->addProperty(prop.first, prop.second.as<nbt::tag_string>().get());
            }
        }

        palette->addBlockState(*state, i);
    }

    palette->finalize();

    return palette;
}

ChunkPalette *ChunkPalette::fromJson(nlohmann::json &json) {
    auto palette = new ChunkPalette();

    for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
        for (auto &e : it.value()["states"]) {
            auto state = new BlockState(it.key());

            if (e.find("properties") != e.end()) {
                for (auto prop_it = e["properties"].begin(); prop_it != e["properties"].end(); ++prop_it) {
                    state->addProperty(prop_it.key(), prop_it.value());
                }
            }

            palette->addBlockState(*state, e["id"]);
        }
    }

    palette->finalize();

    return palette;
}

void ChunkPalette::addBlockState(BlockState &state, uint16_t id) {
    stateToId[state] = id;
    idToState[id] = &state;
}

void ChunkPalette::finalize() {
    bitsPerBlock = ceil(log2(idToState.size()));

    if (bitsPerBlock < 4)
        bitsPerBlock = 4;

    global = bitsPerBlock > 8;
}

uint8_t ChunkPalette::getBitsPerBlock() const {
    return bitsPerBlock;
}

void ChunkPalette::writeToByteArray(std::vector<std::byte> &array) {
    PacketData::writeUnsignedByte(bitsPerBlock, array);

    if (!global) {
        PacketData::writeVarInt(idToState.size(), array);

        for (auto &pair : idToState) {
            PacketData::writeVarInt(Server::get()->getPalette()->getBlockStateId(*pair.second), array);
        }
    }
}

uint16_t ChunkPalette::getBlockStateId(BlockState &state) {
    auto it = stateToId.find(state);
    return it == stateToId.end() ? -1 : it->second;
}

std::string ChunkPalette::toString(bool withMapping) {
    return std::string("Palette{g=") + std::to_string(global) + ",len=" + std::to_string(idToState.size()) + ",bits=" +
           std::to_string(bitsPerBlock) + (withMapping ? ",m=\n" + mappingToString() : ",m=...") + "}";
}

std::string ChunkPalette::mappingToString() {
    std::string str;

    for (auto &pair : idToState) {
        str += std::to_string(pair.first) + " -> " + pair.second->toString();

        if (!global)
            str += std::string(" -> ") + std::to_string(Server::get()->getPalette()->getBlockStateId(*pair.second));

        str += '\n';
    }

    return str;
}

bool ChunkPalette::isGlobal() const {
    return global;
}
