//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETS_H
#define SPICYGOAT_PACKETS_H

#include <spicygoat/protocol.h>
#include <spicygoat/protocol/packets/enum.h>
#include <spicygoat/protocol/packets/handshake/PacketHandshake.h>
#include <spicygoat/protocol/packets/login/PacketLoginStart.h>
#include <spicygoat/protocol/packets/login/PacketLoginSuccess.h>
#include <spicygoat/protocol/packets/login/PacketPluginResponse.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketBlockUpdate.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketChunkData.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketEntityMoveLook.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketExplosion.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketJoinGame.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketKeepAliveCB.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPlayerAbilities.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPlayerInfo.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPlayerLocationCB.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPluginMessageCB.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketServerDifficulty.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketSpawnPosition.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketUnloadChunk.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketChatCommand.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketChatMessageSB.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketClickWindow.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketClientSettings.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketClientStatus.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketEntityAction.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketKeepAliveSB.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketPlayerAbilitiesSB.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketPlayerDigging.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketPlayerLook.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketPlayerPosition.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketPlayerPositionLook.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketPluginMessageSB.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketSetCreativeSlot.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketSetHeldItem.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketTeleportConfirm.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketUseItem.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketUseItemOn.h>
#include <spicygoat/protocol/packets/status/PacketPing.h>
#include <spicygoat/protocol/packets/status/PacketPong.h>
#include <spicygoat/protocol/packets/status/PacketRequest.h>
#include <spicygoat/protocol/packets/status/PacketResponse.h>

namespace Packets {
std::unique_ptr<Packet> parse(PacketData& data, ProtocolState state);
}

#endif  // SPICYGOAT_PACKETS_H
