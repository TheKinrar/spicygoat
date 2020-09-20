//
// Created by thekinrar on 18/09/2020.
//

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <iostream>

#include "../../Server.h"
#include "../../protocol/channels/minecraft/CMBrand.h"
#include "LoginListener.h"
#include "PlayerConnection.h"

LoginListener::LoginListener(TCPConnection& connection) : connection(connection) {}

void LoginListener::onLoginStart(const PacketLoginStart& packet) {
    boost::uuids::uuid uuid = (boost::uuids::random_generator()());

    connection.sendPacket(new PacketLoginSuccess(uuid, packet.name));
    connection.setState(ProtocolState::PLAY);

    EntityPlayer* player = Server::get()->createPlayer(uuid, packet.name, connection);
    connection.setPlayer(player);

    auto pos = Server::get()->getWorld().getSpawnPosition();
    connection.sendPacket(new PacketJoinGame(player));
    CMBrand(std::string("SpicyGoat")).send(connection);
    connection.sendPacket(new PacketServerDifficulty(0));// TODO difficulty
    connection.sendPacket(new PacketSpawnPosition(pos));
    connection.sendPacket(new PacketPlayerAbilities(false, false, true, false, 0.05, 0.1));// TODO player abilities
    connection.sendPacket(
            new PacketPlayerLocationCB(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0)));// TODO player location
    connection.getPlayer()->setNextLocation(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0));

    connection.setListener(std::make_unique<PlayerConnection>(connection, *player));
}
