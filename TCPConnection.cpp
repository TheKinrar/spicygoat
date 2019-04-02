//
// Created by thekinrar on 30/03/19.
//

#include <iostream>
#include <libnet.h>
#include "TCPConnection.h"
#include "protocol/packets/Packet.h"
#include "entities/EntityPlayer.h"
#include "Server.h"

TCPConnection::TCPConnection(int sock, sockaddr_in addr) {
    this->sock = sock;
    this->addr = addr;
}

void TCPConnection::sendPacket(Packet *packet) {
    std::cout << getName() << " <= " << packet->toString() << std::endl;

    std::vector<std::byte> data = packet->bytes();

    std::vector<std::byte> bytes;
    PacketData::writeVarInt(data.size(), bytes);
    bytes.insert(bytes.end(), data.begin(), data.end());

    send(sock, (char*) bytes.data(), bytes.size(), 0);
}

void TCPConnection::task() {
    std::cout << getName() << " connected" << std::endl;

    try {
        read:
        int length = readVarInt();

        char *data = new char[length];
        recv(sock, data, length, 0);

        PacketData packetData(data, length);
        Packet *packet = Packet::parse(&packetData, this);

        std::cout << getName() << " => " << packet->toString() << std::endl;

        packet->handle();
        goto read;
    } catch(std::exception &e) {
        close(sock);
        std::cout << getName() << " disconnected: " << e.what() << std::endl;
    }
}

int TCPConnection::readVarInt() {
    int bytes = 0;
    int result = 0;
    char current;

    do {
        int size;
        if((size = recv(sock, &current, sizeof(current), 0)) < 1) {
            throw std::runtime_error(std::string("Network error: ") + strerror(errno));
        }

        int value = (current & 0b01111111);
        result |= (value << (7 * bytes));

        bytes++;

        if(bytes > 5) {
            throw std::runtime_error("Protocol error: invalid VarInt");
        }

    } while((current & 0b10000000) != 0);

    return result;
}

void TCPConnection::setState(ConnectionState newState) {
    state = newState;
}

ConnectionState TCPConnection::getState() const {
    return state;
}

std::string TCPConnection::getName() {
    return std::string(inet_ntoa(addr.sin_addr)) + ":" + std::to_string(htons(addr.sin_port)) + "/" + std::to_string(state);
}

void TCPConnection::setPlayer(EntityPlayer *newPlayer) {
    this->player = newPlayer;
}
