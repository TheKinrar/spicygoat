//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLUGINMESSAGESB_H
#define SPICYGOAT_PACKETPLUGINMESSAGESB_H


#include "../../ServerBoundPacket.h"

class PacketPluginMessageSB : public ServerBoundPacket {
public:
    explicit PacketPluginMessageSB(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    std::string channel;
};


#endif //SPICYGOAT_PACKETPLUGINMESSAGESB_H
