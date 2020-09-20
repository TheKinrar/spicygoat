//
// Created by thekinrar on 18/09/2020.
//

#include "StatusListener.h"

StatusListener::StatusListener(TCPConnection& connection) : connection(connection) {}

void StatusListener::onRequest(const PacketRequest& request) {
    connection.sendPacket(new PacketResponse());
}

void StatusListener::onPing(const PacketPing& ping) {
    connection.sendPacket(new PacketPong(ping.getPayload()));
}
