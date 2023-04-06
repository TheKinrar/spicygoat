//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_HANDSHAKELISTENER_H
#define SPICYGOAT_HANDSHAKELISTENER_H

#include <spicygoat/protocol/listeners/PacketListenerHandshake.h>

class HandshakeListener : public PacketListenerHandshake {
   public:
    explicit HandshakeListener(std::shared_ptr<TCPConnection> connection);

    void onHandshake(const PacketHandshake &packet) override;

   private:
    std::shared_ptr<TCPConnection> connection;
};

#endif  // SPICYGOAT_HANDSHAKELISTENER_H
