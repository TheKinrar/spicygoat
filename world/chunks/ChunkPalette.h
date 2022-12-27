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
    static std::shared_ptr<ChunkPalette> fromNBT(nbt::tag_list&);
    static std::shared_ptr<ChunkPalette> fromJson(nlohmann::json&);

    uint8_t getBitsPerBlock() const;

    [[nodiscard]]
    int getBlocksPerLong() const {
        return 64 / getBitsPerBlock();
    }

    int16_t getBlockStateId(const BlockState &state) const;

    void writeToByteArray(std::vector<std::byte>&);

    std::string toString(bool withMapping = false);

    [[nodiscard]]
    bool isSingle() const {
        return single;
    }

    [[nodiscard]]
    const BlockState& getSingleBlockState() const {
        return idToState.at(0);
    }

    [[nodiscard]]
    BlockState getBlockState(int16_t id) const {
        return idToState.at(id);
    }

    [[nodiscard]]
    std::shared_ptr<ChunkPalette> grow(BlockState newState) const {
        auto grown = std::make_shared<ChunkPalette>(*this);
        grown->addBlockState(newState, (int16_t) grown->stateToId.size());
        return grown;
    }

    std::string mappingToString();

private:
    void addBlockState(BlockState &state, int16_t id);
    void finalize();

    std::map<BlockState, int16_t> stateToId;
    std::map<int16_t, BlockState> idToState;

    uint8_t bitsPerBlock;

    bool global;
    bool single;
};


#endif //SPICYGOAT_CHUNKPALETTE_H
