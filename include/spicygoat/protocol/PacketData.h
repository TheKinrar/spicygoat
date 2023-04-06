//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETDATA_H
#define SPICYGOAT_PACKETDATA_H

#include <bitset>
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <uuid.h>
#include <vector>

#include <spicygoat/item/ItemStack.h>
#include <spicygoat/world/geo/Position.h>

class PacketData {
   public:
    explicit PacketData(std::shared_ptr<char[]> data, int length = -1, int offset = 0);
    static PacketData fromByteArray(const std::vector<std::byte>& array);

    int remaining();

    bool readBoolean();
    static void writeBoolean(bool val, std::vector<std::byte> &bytes);

    char readByte();
    static void writeByte(int8_t val, std::vector<std::byte> &bytes);

    uint8_t readUnsignedByte();
    static void writeUnsignedByte(uint8_t val, std::vector<std::byte> &bytes);

    int16_t readShort() {
        return readUnsignedShort();
    }
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

    uuids::uuid readUuid();
    static void writeUuid(uuids::uuid, std::vector<std::byte> &);

    float readFloat();
    static void writeFloat(float, std::vector<std::byte> &);

    static void writeAngle(float val, std::vector<std::byte> &bytes) {
        val = std::remainder(val, 360.0f);
        if(val < 0) val += 360;
        writeUnsignedByte(static_cast<uint8_t>((val * 256) / 360), bytes);
    }

    double readDouble();
    static void writeDouble(double, std::vector<std::byte> &);

    int readVarInt();
    static void writeVarInt(int, std::vector<std::byte> &);

    Face readFace() {
        return static_cast<Face>(readVarInt());
    }

    std::string readString();
    static void writeString(const std::string &, std::vector<std::byte> &);

    PacketData readPacketData(size_t len) {
        PacketData ret(data, len, pos);
        pos += len;
        return ret;
    }

    void readByteArray(std::vector<std::byte> &dst, size_t len);

    static void writeByteArray(const std::vector<std::byte> &, std::vector<std::byte> &);
    static void writeByteArray(const std::span<const std::byte> &span, std::vector<std::byte> &to) {
        std::vector<std::byte> temp;
        temp.assign(span.begin(), span.end());
        writeByteArray(temp, to);
    }

    Position readPosition();
    static void writePosition(Position position, std::vector<std::byte> &);

    template <size_t N>
    static void writeBitSet(const std::bitset<N> &bitset, std::vector<std::byte> &bytes) {
        if(bitset.size() > 64) throw std::runtime_error("bitsets of more than 64 bits are not supported");

        if(bitset.size() == 0) {
            writeVarInt(0, bytes);
        } else {
            writeVarInt(1, bytes);
            writeUnsignedLong(bitset.to_ulong(), bytes);
        }
    }

    template <size_t N>
    void readFixedBitSet(std::bitset<N> &dst) {
        for(int i = 1; i < (N + 7) / 8; ++i) {
            dst << 8;
            dst |= readByte();
        }
    }

    template <size_t N>
    static void writeFixedBitSet(const std::bitset<N> &bitset, std::vector<std::byte> &bytes) {
        if(bitset.size() > 8) throw std::runtime_error("bitsets of more than 8 bits are not supported");

        writeByte(bitset.to_ulong() & 0xFF, bytes);
    }

    ItemStack readItemStack() {
        if(readBoolean()) {
            int id = readVarInt();
            int8_t count = readByte();
            if(readByte()) {
                pos--;

                std::istringstream stream;
                stream.rdbuf()->pubsetbuf(data.get() + pos, remaining());
                auto nbt = nbt::io::read_compound(stream).second;
                pos += remaining();

                return {id, count, std::move(nbt)};
            } else {
                return ItemStack(id, count);
            }
        } else {
            return {};
        }
    }

    static void writeItemStack(const ItemStack& is, std::vector<std::byte> &bytes) {
        PacketData::writeBoolean(is.present, bytes);
        if(is.present) {
            PacketData::writeVarInt(is.id, bytes);
            PacketData::writeByte(is.count, bytes);
            if(is.hasNbt) {
                PacketData::writeNbt(*is.nbt, bytes);
            } else {
                PacketData::writeByte(0, bytes);
            }
        }
    }

    static void writeNbt(const nbt::tag& tag, std::vector<std::byte> &bytes) {
        std::ostringstream stream;
        nbt::io::write_tag("", tag, stream);

        auto string = stream.str();
        std::vector<std::byte> vec;
        vec.reserve(string.size());
        for(const auto &item : string)
            vec.push_back(std::byte(item));

        writeByteArray(vec, bytes);
    }

    std::shared_ptr<char[]> data;
    const int offset;
    const int length;
    int pos;
};

#endif  // SPICYGOAT_PACKETDATA_H
