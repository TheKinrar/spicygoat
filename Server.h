//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_SERVER_H
#define SPICYGOAT_SERVER_H

#include "entities/EntityPlayer.h"
#include <vector>
#include <uuid/uuid.h>
#include <string>

class Server {
public:
    static Server* get();

    EntityPlayer* createPlayer(uuid_t &uuid, std::string name);

    int32_t nextEID();

private:
    std::vector<EntityPlayer*> players;



    int32_t next_eid = 0;
    std::vector<Entity*> entities;
};


#endif //SPICYGOAT_SERVER_H
