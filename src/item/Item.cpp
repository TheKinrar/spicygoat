//
// Created by thekinrar on 09/04/23.
//

#include <spicygoat/item/Item.h>
#include <spicygoat/Server.h>

Item::Item(std::string name) : name(std::move(name)) {
    Server::get().getItemRegistry().add(*this);
}
