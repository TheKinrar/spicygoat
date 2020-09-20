//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_LOGINLISTENER_H
#define SPICYGOAT_LOGINLISTENER_H


#include "../PacketListenerLogin.h"

class LoginListener : public PacketListenerLogin {
public:
    explicit LoginListener(TCPConnection &connection);

    void onLoginStart(const PacketLoginStart &packet) override;

private:
    TCPConnection &connection;
};


#endif//SPICYGOAT_LOGINLISTENER_H
