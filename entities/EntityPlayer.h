//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITYPLAYER_H
#define SPICYGOAT_ENTITYPLAYER_H

#include <uuid/uuid.h>
#include <string>
#include "Entity.h"
#include "../world/Location.h"

class EntityPlayer : public Entity {
public:
    EntityPlayer(uuid_t &uuid, std::string& name);

    std::string toString() override;

private:
    uuid_t *uuid;
    std::string name;
};


#endif //SPICYGOAT_ENTITYPLAYER_H
