//
// Created by thekinrar on 03/04/19.
//

#include <io/izlibstream.h>
#include <io/stream_reader.h>
#include <tag_compound.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <spicygoat/Server.h>
#include <spicygoat/world/chunks/Region.h>

std::unique_ptr<Region> Region::load(int32_t x, int32_t z) {
    std::ifstream ifs(std::string("world/region/r." + std::to_string(x) + "." + std::to_string(z) + ".mca"),
                      std::ios::binary | std::ios::ate);
    std::fpos len = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto bytes = std::make_shared<char[]>(len);
    ifs.read(bytes.get(), len);
    ifs.close();

    return std::make_unique<Region>(x, z, std::move(bytes));
}

ChunkColumn &Region::getColumn(int32_t x, int32_t z) {
    auto it = columns.find(Position2D(x, z));

    if(it == columns.end()) {
        columns[Position2D(x, z)] = std::make_unique<ChunkColumn>((this->x * 32) + x, (this->z * 32) + z);
        auto &col = *columns[Position2D(x, z)];

        PacketData header(data);
        header.pos = ((z % 32) * 32 + (x % 32)) * 4;
        uint32_t offset = ((header.readUnsignedByte() & 0x0F) << 16) | ((header.readUnsignedByte() & 0xFF) << 8) |
                          (header.readUnsignedByte() & 0xFF);
        uint8_t size = header.readUnsignedByte();
        if(offset) {
            offset *= 4096;

            PacketData chunkData(data, size);
            chunkData.pos = offset;
            uint32_t chunkSize = chunkData.readUnsignedInt();
            uint8_t chunkCompression = chunkData.readUnsignedByte();

            if(chunkCompression != 2) throw std::runtime_error("Unsupported chunk compression type");

            std::istringstream stream;
            stream.rdbuf()->pubsetbuf(data.get() + offset + 5, chunkSize - 1);
            zlib::izlibstream zs(stream);

            auto nbt = nbt::io::read_compound(zs).second;
            col.setNbt(nbt);
        }

        return col;
    }

    return *it->second;
}
