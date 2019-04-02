//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_PACKETPING_H
#define SPICYGOAT_PACKETPING_H


#include "../ServerBoundPacket.h"

class PacketPing : public ServerBoundPacket {
public:
    explicit PacketPing(PacketData* data, TCPConnection* conn);

    void handle() override;

    int64_t getPayload() const;

    std::string toString() const override;

private:
    TCPConnection* conn;

    int64_t payload;
};


#endif //SPICYGOAT_PACKETPING_H
