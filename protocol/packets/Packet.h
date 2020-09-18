//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKET_H
#define SPICYGOAT_PACKET_H

#include "enum.h"
#include "../PacketData.h"

class Packet {
public:
    explicit Packet(int id);

    int getId() const;

    virtual std::vector<std::byte> bytes() = 0;

    virtual std::string toString() const = 0;

private:
    int id;
};


#endif //SPICYGOAT_PACKET_H
