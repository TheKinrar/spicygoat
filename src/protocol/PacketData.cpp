//
// Created by thekinrar on 30/03/19.
//

#include <spicygoat/protocol/PacketData.h>
#include <spicygoat/util/endian.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>

PacketData::PacketData(std::shared_ptr<char[]> data, int length, int offset)
    : data(std::move(data)), length(length), offset(offset), pos(offset) {}

PacketData PacketData::fromByteArray(const std::vector<std::byte> &array) {
    auto data = std::make_shared<char[]>(array.size());
    for(int i = 0; i < array.size(); ++i) {
        data[i] = static_cast<char>(array.at(i));
    }
    return PacketData(data, array.size());
}

int PacketData::remaining() {
    if(length == -1) return -1;

    return length - (pos - offset);
}

bool PacketData::readBoolean() {
    return readByte();
}

void PacketData::writeBoolean(bool val, std::vector<std::byte> &bytes) {
    bytes.push_back(std::byte(val));
}

char PacketData::readByte() {
    return data[pos++];
}

void PacketData::writeByte(int8_t val, std::vector<std::byte> &bytes) {
    bytes.push_back(std::byte(val));
}

uint8_t PacketData::readUnsignedByte() {
    return readByte();
}

void PacketData::writeUnsignedByte(uint8_t val, std::vector<std::byte> &bytes) {
    bytes.push_back(std::byte(val));
}

void PacketData::writeShort(int16_t val, std::vector<std::byte> &bytes) {
    for(int i = 0; i < 2; i++) {
        bytes.push_back(std::byte(val >> ((1 - i) * 8)));
    }
}

int PacketData::readVarInt() {
    int bytes = 0;
    int result = 0;
    char current;

    do {
        current = readByte();
        int value = (current & 0b01111111);
        result |= (value << (7 * bytes));

        bytes++;

        if(bytes > 5) {
            throw std::runtime_error("Protocol error: invalid VarInt");
        }

    } while((current & 0b10000000) != 0);

    return result;
}

void PacketData::writeVarInt(int value, std::vector<std::byte> &bytes) {
    do {
        uint8_t byte = value & 0b01111111;
        value = (int)((unsigned int)value >> 7);

        if(value) byte |= 0b10000000;

        bytes.push_back(std::byte(byte));
    } while(value);
}

int PacketData::varIntLength(int value) {
    int n = 0;
    do {
        n++;
        value >>= 7;
    } while(value);
    return n;
}

uint16_t PacketData::readUnsignedShort() {
    uint8_t a = readByte();
    uint8_t b = readByte();

    return (((uint16_t)a) << 8) | (0x00ff & b);
}

int32_t PacketData::readInt() {
    int64_t val = be32toh(*((int32_t *)(data.get() + pos)));
    pos += 4;
    return val;
}

void PacketData::writeInt(int32_t val, std::vector<std::byte> &bytes) {
    for(int i = 0; i < 4; i++) {
        bytes.push_back(std::byte(val >> ((3 - i) * 8)));
    }
}

uint32_t PacketData::readUnsignedInt() {
    uint32_t val = be32toh(*((uint32_t *)(data.get() + pos)));
    pos += 4;
    return val;
}

void PacketData::writeUnsignedInt(uint32_t val, std::vector<std::byte> &bytes) {
    for(int i = 0; i < 4; i++) {
        bytes.push_back(std::byte(val >> ((3 - i) * 8)));
    }
}

int64_t PacketData::readLong() {
    int64_t val = be64toh(*((int64_t *)(data.get() + pos)));
    pos += 8;
    return val;
}

void PacketData::writeLong(int64_t val, std::vector<std::byte> &bytes) {
    for(int i = 0; i < 8; i++) {
        bytes.push_back(std::byte(val >> ((7 - i) * 8)));
    }
}

uint64_t PacketData::readUnsignedLong() {
    uint64_t val = be64toh(*((uint64_t *)(data.get() + pos)));
    pos += 8;
    return val;
}

void PacketData::writeUnsignedLong(uint64_t val, std::vector<std::byte> &bytes) {
    for(int i = 0; i < 8; i++) {
        bytes.push_back(std::byte(val >> ((7 - i) * 8)));
    }
}

uuids::uuid PacketData::readUuid() {
    std::array<uuids::uuid::value_type, 16> dst{};
    for(uuids::uuid::value_type &i : dst) {
        i = readUnsignedByte();
    }
    return {dst};
}

void PacketData::writeUuid(uuids::uuid uuid, std::vector<std::byte> &bytes) {
    for(std::byte i : uuid.as_bytes()) {
        writeUnsignedByte(static_cast<uint8_t>(i), bytes);
    }
}

float PacketData::readFloat() {
    int32_t val = readInt();
    return *((float *)(&val));
}

void PacketData::writeFloat(float val, std::vector<std::byte> &bytes) {
    writeUnsignedInt(*(uint32_t *)((float *)(&val)), bytes);
}

double PacketData::readDouble() {
    int64_t val = readLong();
    return *((double *)(&val));
}

void PacketData::writeDouble(double val, std::vector<std::byte> &bytes) {
    writeUnsignedLong(*(uint64_t *)((float *)(&val)), bytes);
}

std::string PacketData::readString() {
    int stringByteLength = readVarInt();
    std::string string(data.get() + pos, stringByteLength);
    pos += stringByteLength;
    return string;
}

void PacketData::writeString(const std::string &string, std::vector<std::byte> &bytes) {
    writeVarInt(string.length(), bytes);

    std::transform(string.begin(), string.end(), std::back_inserter(bytes),
                   [](unsigned char c) { return std::byte(c); });
}

void PacketData::readByteArray(std::vector<std::byte> &dst, size_t len) {
    for(size_t i = 0; i < len; i++) {
        dst.push_back(std::byte(readByte()));
    }
}

void PacketData::writeByteArray(const std::vector<std::byte> &val, std::vector<std::byte> &bytes) {
    bytes.insert(bytes.end(), val.begin(), val.end());
}

Position PacketData::readPosition() {
    uint64_t val = readUnsignedLong();
    uint64_t x = val >> 38;
    if(x >= 1 << 25) x -= 1 << 26;
    uint64_t y = val & 0xFFF;
    if(y >= 1 << 11) y -= 1 << 12;
    uint64_t z = val << 26 >> 38;
    if(z >= 1 << 25) z -= 1 << 26;
    return {(int32_t)x, (int32_t)y, (int32_t)z};
}

void PacketData::writePosition(Position position, std::vector<std::byte> &bytes) {
    uint64_t val = ((((uint64_t)position.getX()) & 0x3FFFFFF) << 38) |
                   ((((uint64_t)position.getZ()) & 0x3FFFFFF) << 12) | (((uint64_t)position.getY()) & 0xFFF);

    writeUnsignedLong(val, bytes);
}
