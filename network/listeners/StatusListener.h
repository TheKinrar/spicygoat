//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_STATUSLISTENER_H
#define SPICYGOAT_STATUSLISTENER_H

#include "../PacketListenerStatus.h"

class StatusListener : public PacketListenerStatus {
   public:
    explicit StatusListener(TCPConnection &connection);

    void onRequest(const PacketRequest &request) override;
    void onPing(const PacketPing &ping) override;

   private:
    TCPConnection &connection;
};

#endif  // SPICYGOAT_STATUSLISTENER_H
