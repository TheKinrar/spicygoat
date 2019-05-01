//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETKEEPALIVESB_H
#define SPICYGOAT_PACKETKEEPALIVESB_H


#include "../../ServerBoundPacket.h"

class PacketKeepAliveSB : public ServerBoundPacket {
public:
    explicit PacketKeepAliveSB(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    int64_t id;
};


#endif //SPICYGOAT_PACKETKEEPALIVESB_H