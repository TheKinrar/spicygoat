#include <iostream>

#include "Server.h"
#include "TCPServer.h"
#include "config/Config.h"

void sigterm_handler(int) {
    std::cout << "Stopping server" << std::endl;

    TCPServer::get().stop();
}

int main() {
    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);

    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, sigterm_handler);

    std::cout << "SpicyGoat is here!" << std::endl;

    Config::get();
    Server::get().run();

    return 0;
}
