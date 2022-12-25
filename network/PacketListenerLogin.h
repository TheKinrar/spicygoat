//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETLISTENERLOGIN_H
#define SPICYGOAT_PACKETLISTENERLOGIN_H


#include "PacketListener.h"

class PacketListenerLogin : public PacketListener {
public:
    void handle(const ServerBoundPacket &packet) override;

    virtual void onLoginStart(const PacketLoginStart&) = 0;
    virtual void onPluginResponse(const PacketPluginResponse&) = 0;
};


#endif //SPICYGOAT_PACKETLISTENERLOGIN_H
