//
// Created by thekinrar on 09/04/19.
//

#ifndef SPICYGOAT_CHUNKPALETTE_H
#define SPICYGOAT_CHUNKPALETTE_H

#include <spicygoat/block/BlockState.h>
#include <tag_list.h>

#include <map>
#include <nlohmann/json.hpp>

class ChunkPalette {
   public:
    static std::shared_ptr<ChunkPalette> fromNBT(nbt::tag_list&);

    uint8_t getBitsPerBlock() const;

    [[nodiscard]]
    int getBlocksPerLong() const {
        return 64 / getBitsPerBlock();
    }

    int16_t getBlockStateId(const std::shared_ptr<BlockState>& state) const;

    void writeToByteArray(std::vector<std::byte>&);

    std::string toString(bool withMapping = false);

    [[nodiscard]]
    bool isSingle() const {
        return single;
    }

    [[nodiscard]]
    const std::shared_ptr<BlockState>& getSingleBlockState() const {
        return idToState.at(0);
    }

    [[nodiscard]]
    std::vector<std::shared_ptr<BlockState>> getBlockStatesByName(const std::string& name) const {
        std::vector<std::shared_ptr<BlockState>> vec;
        for(const auto& item : stateToId) {
            if(item.first->getBlock().getName().toString() == name) {
                vec.push_back(item.first);
            }
        }
        return vec;
    }

    [[nodiscard]]
    const std::shared_ptr<BlockState>& getBlockState(int16_t id) const {
        return idToState.at(id);
    }

    [[nodiscard]]
    std::shared_ptr<ChunkPalette> grow(const std::shared_ptr<BlockState>& newState) const {
        auto grown = std::make_shared<ChunkPalette>(*this);
        grown->addBlockState(newState, (int16_t)grown->stateToId.size());
        grown->finalize();
        return grown;
    }

    std::string mappingToString();

    void loadGlobal();
    void addBlockState(const std::shared_ptr<BlockState>& state, int16_t id);
    void finalize();

   private:
    std::map<std::shared_ptr<BlockState>, int16_t> stateToId;
    std::map<int16_t, std::shared_ptr<BlockState>> idToState;

    uint8_t bitsPerBlock;

    bool global;
    bool single;
};

#endif  // SPICYGOAT_CHUNKPALETTE_H
