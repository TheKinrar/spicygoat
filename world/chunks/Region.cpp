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
#include "../../protocol/PacketData.h"

Region::Region(int32_t x, int32_t z) : x(x), z(z) {
    std::ifstream ifs(std::string("world/region/r." + std::to_string(x) + "." + std::to_string(z) + ".mca"), std::ios::binary | std::ios::ate);
    std::fpos len = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    char *bytes = new char[len];
    ifs.read(bytes, len);
    ifs.close();

    PacketData header(bytes, 4096);

    for(int i = 0; i < 1024; ++i) {
        uint32_t offset = ((header.readUnsignedByte() & 0x0F) << 16) | ((header.readUnsignedByte() & 0xFF) << 8) | (header.readUnsignedByte() & 0xFF);
        uint8_t size = header.readUnsignedByte();

        if(offset != 0) {
            offset *= 4096;

            PacketData chunkData(bytes + offset);
            uint32_t chunkSize = chunkData.readUnsignedInt();
            uint8_t chunkCompression = chunkData.readUnsignedByte();

            if(chunkCompression != 2)
                throw std::runtime_error("Unsupported chunk compression type");

            std::istringstream stream;
            stream.rdbuf()->pubsetbuf(bytes + offset + 5, chunkSize - 1);
            zlib::izlibstream zs(stream);

            try {
                auto nbt = nbt::io::read_compound(zs).second;
                getColumn(i % 32, (int) (i / 32.0))->setNbt(nbt);
            } catch(std::exception &e) {
                std::cerr << e.what() << std::endl;
                std::cerr << i % 32 << "." << (int) (i / 32.0) << std::endl;
            }
        }
    }

    std::cout << "Region " << x << ";" << z << " loaded." << std::endl;
}

ChunkColumn *Region::getColumn(int32_t x, int32_t z) {
    auto it = columns.find(Position2D(x, z));

    if(it == columns.end()) {
        auto column = new ChunkColumn((this->x * 32) + x, (this->z * 32) + z);
        columns[Position2D(x, z)] = column;
        return column;
    }

    return it->second;
}
