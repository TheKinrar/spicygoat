//
// Created by thekinrar on 01/04/19.
//

#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(uuid_t &uuid, std::string& name) {
    this->uuid = &uuid;
    this->name = name;
}

std::string EntityPlayer::toString() {
    return std::string("EntityPlayer{name=") + name + "}";
}
