//
// Created by thekinrar on 31/03/19.
//

#include "PacketLoginStart.h"
#include "../../packets.h"

PacketLoginStart::PacketLoginStart(PacketData *data) : ServerBoundPacket(Packets::S_LOGIN_START) {
    this->name = data->readString();
    this->hasUuid = data->readBoolean();
    data->readUuid(this->uuid);
}

std::string PacketLoginStart::toString() const {
    if(hasUuid) {
      char uuid_str[37];
      uuid_unparse(uuid, uuid_str);

      return std::string("PacketLoginStart{name=") + name
             + ",hasUuid=" + std::to_string(hasUuid)
             + ",uuid=" + uuid_str
             + "}";
    } else {
      return std::string("PacketLoginStart{name=") + name +
             ",hasUuid=" + std::to_string(hasUuid) + "}";
    }
}
