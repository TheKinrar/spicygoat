//
// Created by thekinrar on 18/09/2020.
//

#include <spicygoat/protocol/listeners/PacketListenerLogin.h>

void PacketListenerLogin::handle(const ServerBoundPacket &packet) {
    switch(packet.getId()) {
        case Packets::S_LOGIN_START:
            onLoginStart(dynamic_cast<const PacketLoginStart &>(packet));
            break;
        case Packets::S_PLUGIN_RESPONSE:
            onPluginResponse(dynamic_cast<const PacketPluginResponse &>(packet));
            break;
    }
}
