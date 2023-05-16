//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKET_H
#define SPICYGOAT_PACKET_H

#include <spicygoat/protocol/PacketData.h>
#include <spicygoat/protocol/packets/enum.h>

class Packet {
   public:
    explicit Packet(int id);
    virtual ~Packet() = default;

    [[nodiscard]]
    int getId() const;

    [[nodiscard]]
    virtual std::vector<std::byte> bytes() const = 0;

    [[nodiscard]]
    virtual std::string toString() const = 0;

   private:
    int id;
};

#endif  // SPICYGOAT_PACKET_H
