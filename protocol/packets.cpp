//
// Created by thekinrar on 18/09/2020.
//

#include <sstream>
#include <stdexcept>

#include "packets.h"

Packet *Packets::parse(PacketData *data, ProtocolState state) {
    int id = data->readVarInt();

    if (state == ProtocolState::HANDSHAKE) {
        if (id == 0x00) {
            return new PacketHandshake(data);
        }
    } else if (state == ProtocolState::STATUS) {
        switch (id) {
            case 0x00:
                return new PacketRequest(data);
            case 0x01:
                return new PacketPing(data);
        }
    } else if (state == ProtocolState::LOGIN) {
        switch (id) {
            case 0x00:
                return new PacketLoginStart(data);
        }
    } else if (state == ProtocolState::PLAY) {
        switch (id) {
            case 0x00:
                return new PacketTeleportConfirm(data);
            case 0x03:
                return new PacketChatMessageSB(data);
            case 0x04:
                return new PacketClientStatus(data);
            case 0x05:
                return new PacketClientSettings(data);
            case 0x0B:
                return new PacketPluginMessageSB(data);
            case 0x10:
                return new PacketKeepAliveSB(data);
            case 0x12:
                return new PacketPlayerPosition(data);
            case 0x13:
                return new PacketPlayerPositionLook(data);
            case 0x14:
                return new PacketPlayerLook(data);
            case 0x15:
                return nullptr;// TODO Player
            case 0x1A:
                return new PacketPlayerAbilitiesSB(data);
            case 0x1B:
                return new PacketPlayerDigging(data);
            case 0x1C:
                return new PacketEntityAction(data);
            case 0x2C:
                return nullptr;// TODO Animation
        }
    }

    std::stringstream ss;
    ss << "Protocol error: invalid packet ID 0x" << std::hex << id;
    throw std::runtime_error(ss.str());
}