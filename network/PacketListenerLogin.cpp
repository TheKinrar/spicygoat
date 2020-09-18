//
// Created by thekinrar on 18/09/2020.
//

#include "PacketListenerLogin.h"

void PacketListenerLogin::handle(const ServerBoundPacket &packet) {
    switch(packet.getId()) {
        case Packets::S_LOGIN_START:
            onLoginStart(static_cast<const PacketLoginStart&>(packet));
            break;
    }
}
