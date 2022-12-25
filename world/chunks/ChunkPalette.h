//
// Created by thekinrar on 09/04/19.
//

#ifndef SPICYGOAT_CHUNKPALETTE_H
#define SPICYGOAT_CHUNKPALETTE_H


#include <tag_list.h>
#include <map>
#include "../blocks/BlockState.h"
#include <nlohmann/json.hpp>

class ChunkPalette {
public:
    static ChunkPalette* fromNBT(nbt::tag_list&);
    static ChunkPalette* fromJson(nlohmann::json&);

    uint8_t getBitsPerBlock() const;

    uint16_t getBlockStateId(BlockState &state);

    void writeToByteArray(std::vector<std::byte>&);

    std::string toString(bool withMapping = false);

    [[nodiscard]]
    bool isSingle() const {
        return single;
    }

    [[nodiscard]]
    const BlockState& getSingleBlockState() const {
        return *idToState.at(0);
    }

private:
    void addBlockState(BlockState &state, uint16_t id);
    void finalize();

    std::string mappingToString();

    std::map<BlockState, uint16_t> stateToId;
    std::map<uint16_t, BlockState*> idToState;

    uint8_t bitsPerBlock;

    bool global;
    bool single;
};


#endif //SPICYGOAT_CHUNKPALETTE_H
