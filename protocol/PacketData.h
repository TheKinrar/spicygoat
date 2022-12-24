//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETDATA_H
#define SPICYGOAT_PACKETDATA_H

#include "../world/geo/Position.h"
#include <bitset>
#include <stdexcept>
#include <iostream>
#include <exception>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <uuid/uuid.h>
#include <vector>

class PacketData {
public:
    explicit PacketData(char* data, int length = -1);

    int remaining();

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

    void readUuid(uuid_t&);
    static void writeUuid(const uuid_t&, std::vector<std::byte> &);

    float readFloat();
    static void writeFloat(float, std::vector<std::byte> &);

    double readDouble();
    static void writeDouble(double, std::vector<std::byte> &);

    int readVarInt();
    static void writeVarInt(int, std::vector<std::byte> &);

    std::string readString();
    static void writeString(const std::string&, std::vector<std::byte> &);

    void readByteArray(std::vector<std::byte>& dst, size_t len);
    static void writeByteArray(const std::vector<std::byte> &, std::vector<std::byte> &);

    Position readPosition();
    static void writePosition(Position position, std::vector<std::byte> &);

    template <size_t N>
    static void writeBitSet(const std::bitset<N>& bitset, std::vector<std::byte>& bytes) {
      if(bitset.size() > 64)
        throw std::runtime_error("bitsets of more than 64 bits are not supported");

      if(bitset.size() == 0) {
        writeVarInt(0, bytes);
      } else {
        writeVarInt(1, bytes);
        writeUnsignedLong(bitset.to_ulong(), bytes);
      }
    }

    template <size_t N>
    void readFixedBitSet(std::bitset<N>& dst) {
        for(int i = 1; i < (N+7)/8; ++i) {
            dst << 8;
            dst |= readByte();
        }
    }

    template <size_t N>
    static void writeFixedBitSet(const std::bitset<N>& bitset, std::vector<std::byte>& bytes) {
        if(bitset.size() > 8)
            throw std::runtime_error("bitsets of more than 8 bits are not supported");

        writeByte(bitset.to_ulong() & 0xFF, bytes);
    }

    const char* data;
    const int length;
    int pos;
};


#endif //SPICYGOAT_PACKETDATA_H
