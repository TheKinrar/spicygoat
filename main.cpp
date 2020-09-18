#include <iostream>
#include "TCPServer.h"
#include "Server.h"

void sigterm_handler(int) {
    std::cout << "Stopping server" << std::endl;

    TCPServer::get().stop();
}

int main() {
    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);

    signal(SIGTERM, sigterm_handler);

    std::cout << "SpicyGoat is here!" << std::endl;
    Server::get()->run();

    return 0;
}