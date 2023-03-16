//
// Created by thekinrar on 15/03/23.
//

#include "BossBar.h"

#include <spicygoat/util/uuid.h>

#include "../protocol/packets/play/clientbound/PacketBossBar.h"

BossBar::BossBar() : id(uuids::generate()) {}

BossBar::~BossBar() {
    removeAllPlayers();
}

void BossBar::setTitle(const std::string& title) {
    BossBar::title = title;

    broadcastPacket(PacketBossBar(*this, PacketBossBar::Action::UpdateTitle));
}

void BossBar::setHealth(float health) {
    BossBar::health = health;

    broadcastPacket(PacketBossBar(*this, PacketBossBar::Action::UpdateHealth));
}

void BossBar::setColor(BossBar::Color color) {
    BossBar::color = color;

    broadcastPacket(PacketBossBar(*this, PacketBossBar::Action::UpdateStyle));
}

void BossBar::setDivision(BossBar::Division division) {
    BossBar::division = division;

    broadcastPacket(PacketBossBar(*this, PacketBossBar::Action::UpdateStyle));
}

void BossBar::addPlayer(const std::weak_ptr<EntityPlayer>& player) {
    auto ptr = player.lock();
    if(ptr) {
        if(std::find_if(players.begin(), players.end(), [&ptr](const std::weak_ptr<EntityPlayer>& e) {
               auto ptr2 = e.lock();
               return ptr2 && ptr->getUuid() == ptr2->getUuid();
           }) != players.end())
            return;

        players.push_back(player);
        ptr->getConnection().sendPacket(PacketBossBar(*this, PacketBossBar::Action::Add));
    }
}

void BossBar::removePlayer(const std::weak_ptr<EntityPlayer>& player) {
    auto ptr = player.lock();

    if(ptr) {
        auto erased = std::erase_if(players, [&ptr](const std::weak_ptr<EntityPlayer>& e) {
            auto ptr2 = e.lock();
            return ptr2 && ptr->getUuid() == ptr2->getUuid();
        });

        if(erased) {
            ptr->getConnection().sendPacket(PacketBossBar(*this, PacketBossBar::Action::Remove));
        }
    }
}

void BossBar::removeAllPlayers() {
    broadcastPacket(PacketBossBar(*this, PacketBossBar::Action::Remove));
    players.clear();
}

void BossBar::broadcastPacket(const ClientBoundPacket& packet) {
    auto it = players.begin();
    while(it != players.end()) {
        auto ptr = it->lock();
        if(ptr) {
            ptr->getConnection().sendPacket(packet);
            ++it;
        } else {
            it = players.erase(it);
        }
    }
}
