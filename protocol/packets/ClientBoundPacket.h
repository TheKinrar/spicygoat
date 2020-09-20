//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_CLIENTBOUNDPACKET_H
#define SPICYGOAT_CLIENTBOUNDPACKET_H


#include "Packet.h"

class ClientBoundPacket : public Packet {
public:
    explicit ClientBoundPacket();

    explicit ClientBoundPacket(int id);
};


#endif //SPICYGOAT_CLIENTBOUNDPACKET_H
