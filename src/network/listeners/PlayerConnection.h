//
// Created by thekinrar on 17/09/2020.
//

#ifndef SPICYGOAT_PLAYERCONNECTION_H
#define SPICYGOAT_PLAYERCONNECTION_H

#include <spicygoat/entities/types/EntityPlayer.h>
#include <spicygoat/protocol/listeners/PacketListenerPlay.h>

class PlayerConnection : public PacketListenerPlay {
   public:
    PlayerConnection(TCPConnection &connection, const std::shared_ptr<EntityPlayer>& player);

    void tick() override;

    void onChatCommand(const PacketChatCommand &packet) override;
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
    void onSetHeldItem(const PacketSetHeldItem &packet) override;
    void onClickWindow(const PacketClickWindow &packet) override;

   private:
    TCPConnection &connection;
    std::shared_ptr<EntityPlayer> player;
    int sequence = -1;

    void updateSequence(int sequence);
};

#endif  // SPICYGOAT_PLAYERCONNECTION_H
