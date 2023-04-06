//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_ENUM_H
#define SPICYGOAT_ENUM_H

namespace Packets {
// Handshake SB
static const int S_HANDSHAKE = 0x00;

// Status SB
static const int S_REQUEST = 0x00;
static const int S_PING = 0x01;

// Login SB
static const int S_LOGIN_START = 0x00;
static const int S_PLUGIN_RESPONSE = 0x02;

// Play SB
static const int S_TELEPORT_CONFIRM = 0x00;
static const int S_CHAT_COMMAND = 0x04;
static const int S_CHAT_MESSAGE = 0x05;
static const int S_CLIENT_STATUS = 0x06;
static const int S_CLIENT_SETTINGS = 0x07;
static const int S_CLICK_WINDOW = 0x0A;
static const int S_CLOSE_WINDOW = 0x0B;
static const int S_PLUGIN_MESSAGE = 0x0C;
static const int S_KEEP_ALIVE = 0x11;
static const int S_PLAYER_POSITION = 0x13;
static const int S_PLAYER_POSITION_LOOK = 0x14;
static const int S_PLAYER_LOOK = 0x15;
static const int S_PLAYER_ABILITIES = 0x1B;
static const int S_PLAYER_DIGGING = 0x1C;
static const int S_ENTITY_ACTION = 0x1D;
static const int S_SET_HELD_ITEM = 0x28;
static const int S_SET_CREATIVE_SLOT = 0x2B;
static const int S_USE_ITEM_ON = 0x31;
static const int S_USE_ITEM = 0x32;
}  // namespace Packets

#endif  // SPICYGOAT_ENUM_H
