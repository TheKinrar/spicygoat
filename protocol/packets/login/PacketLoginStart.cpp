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

    conn->sendPacket(new PacketLoginSuccess(uuid, name));
    conn->setState(ConnectionState::PLAY);

    EntityPlayer *player = Server::get()->createPlayer(uuid, name, *conn);
    conn->setPlayer(player);

    auto pos = Server::get()->getWorld().getSpawnPosition();

    conn->sendPacket(new PacketJoinGame(player));
    CMBrand(std::string("SpicyGoat")).send(*conn);
    conn->sendPacket(new PacketServerDifficulty(0)); // TODO difficulty
    conn->sendPacket(new PacketSpawnPosition(pos));
    conn->sendPacket(new PacketPlayerAbilities(false, false, true, false, 0.05, 0.1)); // TODO player abilities
    conn->sendPacket(new PacketPlayerLocationCB(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0))); // TODO player location

    conn->getPlayer()->setNextLocation(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0));
}

std::string PacketLoginStart::toString() const {
    return std::string("PacketLoginStart{name=") + name + "}";
}
