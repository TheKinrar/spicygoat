//
// Created by thekinrar on 03/04/19.
//

#include <fstream>
#include <io/izlibstream.h>
#include <io/stream_reader.h>
#include <tag_compound.h>
#include <iostream>
#include "Region.h"
#include "../../protocol/PacketData.h"

Region::Region(int32_t x, int32_t z) : x(x), z(z) {
    std::ifstream ifs(std::string("/home/thekinrar/temparia/testworld/region/r." + std::to_string(x) + "." + std::to_string(z) + ".mca"), std::ios::binary | std::ios::ate);
    std::fpos len = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    char *bytes = new char[len];
    ifs.read(bytes, len);
    ifs.close();

    PacketData header(bytes, 4096);

    for(int i = 0; i < 1024; ++i) {
        uint32_t offset = ((header.readUnsignedByte() & 0x0F) << 16) | ((header.readUnsignedByte() & 0xFF) << 8) | (header.readUnsignedByte() & 0xFF);
        uint8_t size = header.readUnsignedByte();

        ChunkColumn *column = getColumn(i % 32, (int) (i / 32.0));

        if(offset != 0) {
            offset = (offset - 2) * 4096 + 8192;


        }
    }


    /*zlib::izlibstream buf(ifs);

    try {
        std::cout << nbt::io::read_compound(ifs).second.get() << std::endl;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << x << "." << z << std::endl;
    }*/
}

ChunkColumn *Region::getColumn(int32_t x, int32_t z) {
    auto it = columns.find(Position2D(x, z));

    if(it == columns.end()) {
        auto column = new ChunkColumn(x, z);
        columns[Position2D(x, z)] = column;
        return column;
    }

    return it->second;
}
