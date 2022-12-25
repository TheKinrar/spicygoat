//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETPLUGINRESPONSE_H
#define SPICYGOAT_PACKETPLUGINRESPONSE_H


#include "../ServerBoundPacket.h"

class PacketPluginResponse : public ServerBoundPacket {
public:
    explicit PacketPluginResponse(PacketData* data) : ServerBoundPacket(Packets::S_PLUGIN_RESPONSE),
            id(data->readVarInt()),
            successful(data->readBoolean()) {
        if(successful) {
            data->readByteArray(this->data, data->remaining());
        }
    };

    [[nodiscard]]
    std::string toString() const override {
        return std::string("PacketPluginResponse{id=") + std::to_string(id)
                + ",successful=" + std::to_string(successful)
                + ",data=" + std::to_string(data.size()) + "B}";
    }

    const int id;
    const bool successful;
    std::vector<std::byte> data;
};


#endif //SPICYGOAT_PACKETPLUGINRESPONSE_H
