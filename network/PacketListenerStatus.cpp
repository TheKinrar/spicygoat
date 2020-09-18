//
// Created by thekinrar on 18/09/2020.
//

#include "PacketListenerStatus.h"

void PacketListenerStatus::handle(const ServerBoundPacket &packet) {
    switch(packet.getId()) {
        case Packets::S_REQUEST:
            onRequest(static_cast<const PacketRequest&>(packet));
            break;
        case Packets::S_PING:
            onPing(static_cast<const PacketPing&>(packet));
            break;
    }
}
