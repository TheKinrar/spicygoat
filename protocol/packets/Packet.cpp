//
// Created by thekinrar on 30/03/19.
//

#include <stdexcept>
#include <sstream>
#include "Packet.h"
#include "handshake/PacketHandshake.h"
#include "status/PacketRequest.h"
#include "status/PacketPing.h"
#include "login/PacketLoginStart.h"
#include "play/serverbound/PacketClientSettings.h"
#include "play/serverbound/PacketPluginMessageSB.h"
#include "play/serverbound/PacketTeleportConfirm.h"
#include "play/serverbound/PacketPlayerPositionLook.h"
#include "play/serverbound/PacketClientStatus.h"
#include "play/serverbound/PacketPlayerPosition.h"
#include "play/serverbound/PacketPlayerLook.h"
#include "play/serverbound/PacketKeepAliveSB.h"
#include "play/serverbound/PacketEntityAction.h"
#include "play/serverbound/PacketPlayerAbilitiesSB.h"

Packet* Packet::parse(PacketData* data, TCPConnection* conn) {
    int id = data->readVarInt();

    if(conn->getState() == ConnectionState::HANDSHAKE) {
        if(id == 0x00) {
            return new PacketHandshake(data, conn);
        }
    } else if(conn->getState() == ConnectionState::STATUS) {
        switch(id) {
            case 0x00:
                return new PacketRequest(data, conn);
            case 0x01:
                return new PacketPing(data, conn);
        }
    } else if(conn->getState() == ConnectionState::LOGIN) {
        switch(id) {
            case 0x00:
                return new PacketLoginStart(data, conn);
        }
    } else if(conn->getState() == ConnectionState::PLAY) {
        switch(id) {
            case 0x00:
                return new PacketTeleportConfirm(data, conn);
            case 0x03:
                return new PacketClientStatus(data, conn);
            case 0x04:
                return new PacketClientSettings(data, conn);
            case 0x0A:
                return new PacketPluginMessageSB(data, conn);
            case 0x0E:
                return new PacketKeepAliveSB(data, conn);
            case 0x10:
                return new PacketPlayerPosition(data, conn);
            case 0x11:
                return new PacketPlayerPositionLook(data, conn);
            case 0x12:
                return new PacketPlayerLook(data, conn);
            case 0x17:
                return new PacketPlayerAbilitiesSB(data, conn);
            case 0x19:
                return new PacketEntityAction(data, conn);
        }
    }

    std::stringstream ss;
    ss << "Protocol error: invalid packet ID 0x" << std::hex << id;
    throw std::runtime_error(ss.str());
}
