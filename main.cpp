#include <iostream>
#include "TCPServer.h"
#include "Server.h"
#include "protocol/packets/play/clientbound/PacketChunkData.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);

    //std::cout << Server::get()->getWorld().getChunk(-1, 0)->getChunk(0)->getPalette()->toString(true) << std::endl;

    TCPServer server = TCPServer();
    std::thread tcpThread(&TCPServer::accept, &server);

    while(server.isRunning()) {
        auto tickStart = std::chrono::system_clock::now();
        Server::get()->tick();
        long tickTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tickStart).count();

        if(tickTime < 50000) {
            std::this_thread::sleep_for(std::chrono::microseconds(50000 - tickTime));
        }
    }

    return 0;
}