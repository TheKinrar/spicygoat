//
// Created by thekinrar on 09/04/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/item/Item.h>

Item::Item(std::string name) : name(std::move(name)) {
    Server::get().getItemRegistry().add(*this);
}
