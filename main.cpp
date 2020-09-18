#include <iostream>
#include "TCPServer.h"
#include "Server.h"

void sigterm_handler(int) {
    std::cout << "Stopping server" << std::endl;

    TCPServer::get().stop();
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);

    signal(SIGTERM, sigterm_handler);

    std::thread tcpThread(&TCPServer::accept, &TCPServer::get());

    while(TCPServer::get().isRunning()) {
        auto tickStart = std::chrono::system_clock::now();
        Server::get()->tick();
        long tickTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tickStart).count();

        if(tickTime < 50000) {
            std::this_thread::sleep_for(std::chrono::microseconds(50000 - tickTime));
        }
    }

    tcpThread.join();

    return 0;
}