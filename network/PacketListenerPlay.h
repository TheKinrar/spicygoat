//
// Created by thekinrar on 17/09/2020.
//

#ifndef SPICYGOAT_PACKETLISTENERPLAY_H
#define SPICYGOAT_PACKETLISTENERPLAY_H

#include "PacketListener.h"

class PacketListenerPlay : public PacketListener {
   public:
    void handle(const ServerBoundPacket& packet) override;

    virtual void onChatMessage(const PacketChatMessageSB& packet) = 0;
    virtual void onTeleportConfirm(const PacketTeleportConfirm& packet) = 0;
    virtual void onClientStatus(const PacketClientStatus& packet) = 0;
    virtual void onClientSettings(const PacketClientSettings& packet) = 0;
    virtual void onPluginMessage(const PacketPluginMessageSB& packet) = 0;
    virtual void onKeepAlive(const PacketKeepAliveSB& packet) = 0;
    virtual void onPlayerPosition(const PacketPlayerPosition& packet) = 0;
    virtual void onPlayerPositionLook(const PacketPlayerPositionLook& packet) = 0;
    virtual void onPlayerLook(const PacketPlayerLook& packet) = 0;
    virtual void onPlayerAbilities(const PacketPlayerAbilitiesSB& packet) = 0;
    virtual void onPlayerDigging(const PacketPlayerDigging& packet) = 0;
    virtual void onEntityAction(const PacketEntityAction& packet) = 0;
    virtual void onSetCreativeSlot(const PacketSetCreativeSlot& packet) = 0;
    virtual void onUseItemOn(const PacketUseItemOn& packet) = 0;
};

#endif  // SPICYGOAT_PACKETLISTENERPLAY_H
