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
#include "play/serverbound/PacketPlayerDigging.h"

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
            case 0x04:
                return new PacketClientStatus(data, conn);
            case 0x05:
                return new PacketClientSettings(data, conn);
            case 0x0B:
                return new PacketPluginMessageSB(data, conn);
            case 0x10:
                return new PacketKeepAliveSB(data, conn);
            case 0x12:
                return new PacketPlayerPosition(data, conn);
            case 0x13:
                return new PacketPlayerPositionLook(data, conn);
            case 0x14:
                return new PacketPlayerLook(data, conn);
            case 0x15:
                return nullptr; // TODO Player
            case 0x1A:
                return new PacketPlayerAbilitiesSB(data, conn);
            case 0x1B:
                return new PacketPlayerDigging(data, conn);
            case 0x1C:
                return new PacketEntityAction(data, conn);
            case 0x2C:
                return nullptr; // TODO Animation
        }
    }

    std::stringstream ss;
    ss << "Protocol error: invalid packet ID 0x" << std::hex << id;
    throw std::runtime_error(ss.str());
}
