//
// Created by thekinrar on 06/01/23.
//

#include "ItemRegistry.h"

#include "../Server.h"
#include "BlockItem.h"

void ItemRegistry::addMapping(const std::string& key, int32_t id) {
    Registry::addMapping(key, id);

    if(!contains(id)) {
        // We don't have any special behaviour for this item. Let's find a generic class for it.

        auto sameNameBlocks = Server::get().getPalette()->getBlockStatesByName(key);
        if(sameNameBlocks.empty()) {
            // Too bad. Generic item it is, then.
            add(std::make_unique<Item>(key));
        } else {
            // Yay! We'll default to placing the first state.
            addBlockItem(std::make_unique<BlockItem>(key, sameNameBlocks.front()->getBlock()));
        }
    }
}

ItemStack ItemRegistry::getLoot(const std::shared_ptr<BlockState>& block) const {
    auto it = blockItems.find(block->getBlock().getName().toString());
    if(it == blockItems.end())
        return {};
    else
        return ItemStack(it->second);
}
