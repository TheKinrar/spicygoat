//
// Created by thekinrar on 17/09/2020.
//

#ifndef SPICYGOAT_PLAYERCONNECTION_H
#define SPICYGOAT_PLAYERCONNECTION_H

#include "../../entities/EntityPlayer.h"
#include "../PacketListenerPlay.h"

class PlayerConnection : public PacketListenerPlay {
   public:
    PlayerConnection(TCPConnection &connection, EntityPlayer &player);

    void onChatMessage(const PacketChatMessageSB &packet) override;
    void onTeleportConfirm(const PacketTeleportConfirm &packet) override;
    void onClientStatus(const PacketClientStatus &packet) override;
    void onClientSettings(const PacketClientSettings &packet) override;
    void onPluginMessage(const PacketPluginMessageSB &packet) override;
    void onKeepAlive(const PacketKeepAliveSB &packet) override;
    void onPlayerPosition(const PacketPlayerPosition &packet) override;
    void onPlayerPositionLook(const PacketPlayerPositionLook &packet) override;
    void onPlayerLook(const PacketPlayerLook &packet) override;
    void onPlayerAbilities(const PacketPlayerAbilitiesSB &packet) override;
    void onPlayerDigging(const PacketPlayerDigging &packet) override;
    void onEntityAction(const PacketEntityAction &packet) override;
    void onSetCreativeSlot(const PacketSetCreativeSlot &packet) override;
    void onUseItemOn(const PacketUseItemOn &packet) override;

   private:
    TCPConnection &connection;
    EntityPlayer &player;
};

#endif  // SPICYGOAT_PLAYERCONNECTION_H
