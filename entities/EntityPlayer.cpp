//
// Created by thekinrar on 01/04/19.
//

#include <iostream>
#include "EntityPlayer.h"
#include "../Server.h"
#include "../protocol/packets/play/clientbound/PacketUnloadChunk.h"
#include "../protocol/packets/play/clientbound/PacketChunkData.h"

EntityPlayer::EntityPlayer(uuid_t &uuid, std::string& name, TCPConnection &conn) : conn(conn) {
    this->uuid = &uuid;
    this->name = name;
}

void EntityPlayer::tick() {
    Entity::tick();

    if(loadedChunks.empty())
        chunkChanged();

    int n = 0;

    for(auto it : std::map(loadingChunks)) {
        auto chunk = it.second;

        if(chunk->hasData()) {
            conn.sendPacket(new PacketChunkData(*chunk));
        } else {
            std::cerr << "no data for column " << chunk->toString() << std::endl;
        }

        loadingChunks.erase(it.first);

        /*++n;
        if(n == 20)
            break;*/
    }
}

void EntityPlayer::chunkChanged() {
    int32_t min_x = getLocation().getChunkX() - 10;
    int32_t max_x = getLocation().getChunkX() + 10;
    int32_t min_z = getLocation().getChunkZ() - 10;
    int32_t max_z = getLocation().getChunkZ() + 10;

    for(auto it : loadedChunks) {
        auto chunk = it.second;

        if(chunk->getX() < min_x || chunk->getX() > max_x || chunk->getZ() < min_z || chunk->getZ() > max_z) {
            conn.sendPacket(new PacketUnloadChunk(*chunk));
            loadedChunks.erase(it.first);
        }
    }

    for(int32_t x = min_x; x <= max_x; ++x) {
        for(int32_t z = min_z; z <= max_z; ++z) {
            Position2D pos(x, z);

            if(loadedChunks.find(pos) == loadedChunks.end()) {
                ChunkColumn *column = Server::get()->getWorld().getChunk(x, z);

                loadingChunks[pos] = column;
                loadedChunks[pos] = column;
            }
        }
    }
}

std::string EntityPlayer::toString() {
    return std::string("EntityPlayer{name=") + name + "}";
}
