//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_HANDSHAKELISTENER_H
#define SPICYGOAT_HANDSHAKELISTENER_H


#include "../PacketListenerHandshake.h"

class HandshakeListener : public PacketListenerHandshake {
public:
    explicit HandshakeListener(TCPConnection& connection);

    void onHandshake(const PacketHandshake& packet) override;

private:
    TCPConnection& connection;
};


#endif//SPICYGOAT_HANDSHAKELISTENER_H
