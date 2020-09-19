//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETDATA_H
#define SPICYGOAT_PACKETDATA_H

#include <netinet/in.h>
#include <exception>
#include <string>
#include <vector>
#include <uuid/uuid.h>
#include "../world/geo/Position.h"

class PacketData {
public:
    explicit PacketData(char* data, int length = -1);

    bool readBoolean();
    static void writeBoolean(bool val, std::vector<std::byte> &bytes);

    char readByte();
    static void writeByte(int8_t val, std::vector<std::byte> &bytes);

    uint8_t readUnsignedByte();
    static void writeUnsignedByte(uint8_t val, std::vector<std::byte> &bytes);

    static void writeShort(int16_t val, std::vector<std::byte> &bytes);

    uint16_t readUnsignedShort();

    int32_t readInt();
    static void writeInt(int32_t, std::vector<std::byte> &);

    uint32_t readUnsignedInt();
    static void writeUnsignedInt(uint32_t, std::vector<std::byte> &);

    int64_t readLong();
    static void writeLong(int64_t, std::vector<std::byte> &);

    uint64_t readUnsignedLong();
    static void writeUnsignedLong(uint64_t, std::vector<std::byte> &);

    static void writeUuid(const uuid_t&, std::vector<std::byte> &);

    float readFloat();
    static void writeFloat(float, std::vector<std::byte> &);

    double readDouble();
    static void writeDouble(double, std::vector<std::byte> &);

    int readVarInt();
    static void writeVarInt(int, std::vector<std::byte> &);

    std::string readString();
    static void writeString(const std::string&, std::vector<std::byte> &);

    static void writeByteArray(const std::vector<std::byte> &, std::vector<std::byte> &);

    Position readPosition();
    static void writePosition(Position position, std::vector<std::byte> &);

private:
    char* data;
    int length;
    int pos;
};


#endif //SPICYGOAT_PACKETDATA_H
