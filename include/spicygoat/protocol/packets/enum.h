//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_ENUM_H
#define SPICYGOAT_ENUM_H

namespace Packets {
// Handshake SB
static const int S_HANDSHAKE = 0x00;

// Status CB
static const int S_RESPONSE = 0x00;
static const int S_PONG = 0x01;

// Status SB
static const int S_REQUEST = 0x00;
static const int S_PING = 0x01;

// Login CB
static const int C_LOGIN_SUCCESS = 0x02;
static const int C_PLUGIN_REQUEST = 0x04;

// Login SB
static const int S_LOGIN_START = 0x00;
static const int S_PLUGIN_RESPONSE = 0x02;

// Play CB
static const int C_SPAWN_ENTITY = 0x01;
static const int C_SPAWN_PLAYER = 0x03;
static const int C_ACK_ACTION = 0x06;
static const int C_BLOCK_UPDATE = 0x0A;
static const int C_BOSS_BAR = 0x0B;
static const int C_SERVER_DIFFICULTY = 0x0C;
static const int C_SET_INVENTORY_CONTENT = 0x12;
static const int C_SET_INVENTORY_SLOT = 0x14;
static const int C_PLUGIN_MESSAGE = 0x17;
static const int C_UNLOAD_CHUNK = 0x1E;
static const int C_GAME_EVENT = 0x1F;
static const int C_KEEP_ALIVE = 0x23;
static const int C_CHUNK_DATA = 0x24;
static const int C_JOIN_GAME = 0x28;
static const int C_ENTITY_MOVE = 0x2B;
static const int C_ENTITY_MOVE_LOOK = 0x2C;
static const int C_ENTITY_LOOK = 0x2D;
static const int C_PLAYER_ABILITIES = 0x34;
static const int C_PLAYER_INFO_REMOVE = 0x39;
static const int C_PLAYER_INFO = 0x3A;
static const int C_PLAYER_LOCATION = 0x3C;
static const int C_DESTROY_ENTITIES = 0x3E;
static const int C_ENTITY_HEAD_ROTATION = 0x42;
static const int C_RENDER_CENTER = 0x4E;
static const int C_SPAWN_POSITION = 0x50;
static const int C_SET_ENTITY_METADATA = 0x52;
static const int C_CHAT_MESSAGE = 0x64;
static const int C_PICKUP_ITEM = 0x67;
static const int C_TELEPORT_ENTITY = 0x68;
static const int C_UPDATE_TAGS = 0x6E;

// Play SB
static const int S_TELEPORT_CONFIRM = 0x00;
static const int S_CHAT_COMMAND = 0x04;
static const int S_CHAT_MESSAGE = 0x05;
static const int S_PLAYER_SESSION = 0x06;
static const int S_CLIENT_STATUS = 0x07;
static const int S_CLIENT_SETTINGS = 0x08;
static const int S_CLICK_WINDOW = 0x0B;
static const int S_CLOSE_WINDOW = 0x0C;
static const int S_PLUGIN_MESSAGE = 0x0D;
static const int S_KEEP_ALIVE = 0x12;
static const int S_PLAYER_POSITION = 0x14;
static const int S_PLAYER_POSITION_LOOK = 0x15;
static const int S_PLAYER_LOOK = 0x16;
static const int S_PLAYER_ON_GROUND = 0x17;
static const int S_PLAYER_ABILITIES = 0x1C;
static const int S_PLAYER_DIGGING = 0x1D;
static const int S_ENTITY_ACTION = 0x1E;
static const int S_SET_HELD_ITEM = 0x28;
static const int S_SET_CREATIVE_SLOT = 0x2B;
static const int S_SWING_ARM = 0x2F;
static const int S_USE_ITEM_ON = 0x31;
static const int S_USE_ITEM = 0x32;
}  // namespace Packets

#endif  // SPICYGOAT_ENUM_H
