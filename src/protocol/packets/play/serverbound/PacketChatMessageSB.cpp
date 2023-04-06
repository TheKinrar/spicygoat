//
// Created by thekinrar on 18/09/2020.
//

#include <spicygoat/protocol/packets/play/serverbound/PacketChatMessageSB.h>

PacketChatMessageSB::PacketChatMessageSB(PacketData& data) : ServerBoundPacket(Packets::S_CHAT_MESSAGE) {
    this->message = data.readString();
    this->timestamp = data.readLong();
    this->salt = data.readLong();
    this->hasSignature = data.readBoolean();
    if(hasSignature) {
        data.readByteArray(this->signature, 256);
    }
    this->count = data.readVarInt();
    this->ackOffset = data.readVarInt();
    data.readFixedBitSet(this->ack);
}

std::string PacketChatMessageSB::toString() const {
    return std::string("PacketChatMessageSB{") + message + "}";
}
