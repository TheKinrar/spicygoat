//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETS_H
#define SPICYGOAT_PACKETS_H

#include "../protocol.h"

#include "packets/enum.h"

#include "packets/handshake/PacketHandshake.h"

#include "packets/status/PacketPing.h"
#include "packets/status/PacketPong.h"
#include "packets/status/PacketRequest.h"
#include "packets/status/PacketResponse.h"

#include "packets/login/PacketLoginStart.h"
#include "packets/login/PacketLoginSuccess.h"
#include "packets/login/PacketPluginResponse.h"

#include "packets/play/clientbound/PacketChunkData.h"
#include "packets/play/clientbound/PacketEntityMoveLook.h"
#include "packets/play/clientbound/PacketJoinGame.h"
#include "packets/play/clientbound/PacketKeepAliveCB.h"
#include "packets/play/clientbound/PacketPlayerAbilities.h"
#include "packets/play/clientbound/PacketPlayerInfo.h"
#include "packets/play/clientbound/PacketPlayerLocationCB.h"
#include "packets/play/clientbound/PacketPluginMessageCB.h"
#include "packets/play/clientbound/PacketServerDifficulty.h"
#include "packets/play/clientbound/PacketSpawnPosition.h"
#include "packets/play/clientbound/PacketUnloadChunk.h"

#include "packets/play/serverbound/PacketChatMessageSB.h"
#include "packets/play/serverbound/PacketClientSettings.h"
#include "packets/play/serverbound/PacketClientStatus.h"
#include "packets/play/serverbound/PacketEntityAction.h"
#include "packets/play/serverbound/PacketKeepAliveSB.h"
#include "packets/play/serverbound/PacketPlayerAbilitiesSB.h"
#include "packets/play/serverbound/PacketPlayerDigging.h"
#include "packets/play/serverbound/PacketPlayerLook.h"
#include "packets/play/serverbound/PacketPlayerPosition.h"
#include "packets/play/serverbound/PacketPlayerPositionLook.h"
#include "packets/play/serverbound/PacketPluginMessageSB.h"
#include "packets/play/serverbound/PacketSetCreativeSlot.h"
#include "packets/play/serverbound/PacketTeleportConfirm.h"
#include "packets/play/serverbound/PacketUseItemOn.h"

namespace Packets {
    std::unique_ptr<Packet> parse(PacketData& data, ProtocolState state);
}

#endif //SPICYGOAT_PACKETS_H
