//
// Created by thekinrar on 18/09/2020.
//

#include <spicygoat/protocol/listeners/PacketListenerHandshake.h>

void PacketListenerHandshake::handle(const ServerBoundPacket &packet) {
    switch(packet.getId()) {
        case Packets::S_HANDSHAKE:
            onHandshake(static_cast<const PacketHandshake &>(packet));
            break;
    }
}
