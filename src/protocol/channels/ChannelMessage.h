//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_CHANNELMESSAGE_H
#define SPICYGOAT_CHANNELMESSAGE_H

#include <spicygoat/TCPConnection.h>

#include <string>
#include <vector>

class ChannelMessage {
   public:
    explicit ChannelMessage(const char* channel);

    void send(std::vector<std::byte> data, TCPConnection& conn);

    virtual std::string toString() = 0;

   private:
    std::string channel;
};

#endif  // SPICYGOAT_CHANNELMESSAGE_H
