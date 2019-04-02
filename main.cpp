#include <iostream>
#include "TCPServer.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    TCPServer server = TCPServer();

    accept:
    server.accept();
    goto accept;

    return 0;
}