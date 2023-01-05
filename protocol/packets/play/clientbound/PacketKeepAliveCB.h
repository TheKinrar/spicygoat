//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETKEEPALIVECB_H
#define SPICYGOAT_PACKETKEEPALIVECB_H


#include "../../ClientBoundPacket.h"

class PacketKeepAliveCB : public ClientBoundPacket {
public:
    explicit PacketKeepAliveCB(int64_t id);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

private:
    int64_t id;
};


#endif //SPICYGOAT_PACKETKEEPALIVECB_H
