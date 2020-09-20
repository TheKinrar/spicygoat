//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_CMBRAND_H
#define SPICYGOAT_CMBRAND_H


#include "../ChannelMessage.h"

class CMBrand : public ChannelMessage {
public:
    explicit CMBrand(std::string brand);

    void send(TCPConnection& conn);

    std::string toString() override;

private:
    std::string brand;
};


#endif//SPICYGOAT_CMBRAND_H
