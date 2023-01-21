#include <csignal>
#include <iostream>

#include "Server.h"
#include "TCPServer.h"

void sigterm_handler(int) {
    TCPServer::get().stop();
}

int main() {
    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);

#ifdef __linux__
    signal(SIGPIPE, SIG_IGN);
#endif
    signal(SIGTERM, sigterm_handler);

    Server::get().run();

    return 0;
}
