//
// Created by thekinrar on 03/04/19.
//

#include <fstream>
#include <io/izlibstream.h>
#include <io/stream_reader.h>
#include <tag_compound.h>
#include <iostream>
#include <sstream>
#include "Region.h"

std::unique_ptr<Region> Region::load(int32_t x, int32_t z) {
    std::ifstream ifs(std::string("world/region/r." + std::to_string(x) + "." + std::to_string(z) + ".mca"), std::ios::binary | std::ios::ate);
    std::fpos len = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    char *bytes = new char[len];
    ifs.read(bytes, len);
    ifs.close();

    return std::make_unique<Region>(x, z, bytes);
}

ChunkColumn &Region::getColumn(int32_t x, int32_t z) {
    auto it = columns.find(Position2D(x, z));

    if(it == columns.end()) {
        columns[Position2D(x, z)] = std::make_unique<ChunkColumn>((this->x * 32) + x, (this->z * 32) + z);
        auto& col = *columns[Position2D(x, z)];

        PacketData header(data + ((z % 32) * 32 + (x % 32)) * 4);
        uint32_t offset = ((header.readUnsignedByte() & 0x0F) << 16) | ((header.readUnsignedByte() & 0xFF) << 8) | (header.readUnsignedByte() & 0xFF);
        uint8_t size = header.readUnsignedByte();
        if(offset) {
            offset *= 4096;

            PacketData chunkData(data + offset, size);
            uint32_t chunkSize = chunkData.readUnsignedInt();
            uint8_t chunkCompression = chunkData.readUnsignedByte();

            if(chunkCompression != 2)
                throw std::runtime_error("Unsupported chunk compression type");

            std::istringstream stream;
            stream.rdbuf()->pubsetbuf(data + offset + 5, chunkSize - 1);
            zlib::izlibstream zs(stream);

            try {
                auto nbt = nbt::io::read_compound(zs).second;
                col.setNbt(nbt);
            } catch(std::exception &e) {
                std::cerr << e.what() << std::endl;
                std::cerr << x << "." << z << std::endl;
            }

//            std::cout << "Chunk " << col.getPosition2D() << ";" << z << " loaded." << std::endl;
        }

        return col;
    }

    return *it->second;
}
