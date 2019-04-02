//
// Created by thekinrar on 31/03/19.
//

#include "PacketLoginStart.h"
#include "PacketLoginSuccess.h"
#include "../../../Server.h"
#include "../play/clientbound/PacketJoinGame.h"
#include "../../channels/minecraft/CMBrand.h"
#include "../play/clientbound/PacketServerDifficulty.h"
#include "../play/clientbound/PacketSpawnPosition.h"
#include "../play/clientbound/PacketPlayerAbilities.h"
#include "../play/clientbound/PacketPlayerLocationCB.h"
#include "../play/clientbound/PacketChunkData.h"

#include <uuid/uuid.h>

PacketLoginStart::PacketLoginStart(PacketData *data, TCPConnection *conn) {
    this->conn = conn;

    this->name = data->readString();
}

void PacketLoginStart::handle() {
    uuid_t uuid;
    uuid_generate(uuid);

    EntityPlayer *player = Server::get()->createPlayer(uuid, name);
    conn->setPlayer(player);

    conn->sendPacket(new PacketLoginSuccess(uuid, name));
    conn->setState(ConnectionState::PLAY);
    conn->sendPacket(new PacketJoinGame(player));
    CMBrand(std::string("SpicyGoat")).send(*conn);
    conn->sendPacket(new PacketServerDifficulty(0)); // TODO difficulty
    conn->sendPacket(new PacketSpawnPosition(Position(0, 0, 0))); // TODO world spawn position
    conn->sendPacket(new PacketPlayerAbilities(false, false, false, false, 0.05, 0.1)); // TODO player abilities
    conn->sendPacket(new PacketPlayerLocationCB(Location(0, 100, 0, 0, 0)));

    ChunkColumn chunks(0, 0);
    ChunkColumn chunks2(1, 0);
    ChunkColumn chunks3(0, 1);
    ChunkColumn chunks4(1, 1);
    conn->sendPacket(new PacketChunkData(chunks));
    conn->sendPacket(new PacketChunkData(chunks2));
    conn->sendPacket(new PacketChunkData(chunks3));
    conn->sendPacket(new PacketChunkData(chunks4));
}

std::string PacketLoginStart::toString() const {
    return std::string("PacketLoginStart{name=") + name + "}";
}
