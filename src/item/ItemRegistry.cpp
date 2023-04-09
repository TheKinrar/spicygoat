//
// Created by thekinrar on 06/01/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/item/BlockItem.h>
#include <spicygoat/item/ItemRegistry.h>

ItemStack ItemRegistry::getLoot(const std::shared_ptr<BlockState>& block) const {
    auto it = blockItems.find(block->getBlock().getName().toString());
    if(it == blockItems.end())
        return {};
    else
        return ItemStack(getId(it->second.get().getName()));
}
