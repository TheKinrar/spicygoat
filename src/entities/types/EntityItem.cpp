//
// Created by thekinrar on 07/01/23.
//

#include "EntityItem.h"

#include "../../Server.h"
#include "../../protocol/packets/play/clientbound/PacketPickupItem.h"
#include "../../tracking/PlayerTracker.h"

void EntityItem::tick() {
    Entity::tick();

    const auto& players = dynamic_cast<PlayerTracker&>(getTracker()).getPlayers();
    for(const auto& player : players) {
        if(player->getLocation().distanceSquared(getLocation()) < 1 ||
           player->getLocation().add(0,1,0).distanceSquared(getLocation()) < 1) {
            auto remaining = player->inventory->add(stack);

            if(remaining.count != stack.count) {
                player->getConnection().sendPacket(PacketPickupItem(getEID(), player->getEID(), stack.count - remaining.count));
                if(!remaining.present) {
                    Server::get().removeEntity(*this);
                } else {
                    stack = remaining;
                }
            }
        }
    }
}
