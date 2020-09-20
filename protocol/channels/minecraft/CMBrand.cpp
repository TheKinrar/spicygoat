//
// Created by thekinrar on 01/04/19.
//

#include "CMBrand.h"

CMBrand::CMBrand(std::string brand) : ChannelMessage("minecraft:brand") {
    this->brand = brand;
}

void CMBrand::send(TCPConnection& conn) {
    std::vector<std::byte> data;
    PacketData::writeString(brand, data);

    ChannelMessage::send(data, conn);
}

std::string CMBrand::toString() {
    return std::string("ChannelMessage{channel=minecraft:brand,brand=") + brand + "}";
}
