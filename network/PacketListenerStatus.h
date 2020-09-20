//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETLISTENERSTATUS_H
#define SPICYGOAT_PACKETLISTENERSTATUS_H


#include "PacketListener.h"

class PacketListenerStatus : public PacketListener {
public:
    void handle(const ServerBoundPacket &packet) override;

    virtual void onRequest(const PacketRequest &) = 0;

    virtual void onPing(const PacketPing &) = 0;
};


#endif //SPICYGOAT_PACKETLISTENERSTATUS_H
