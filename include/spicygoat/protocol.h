//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PROTOCOL_H
#define SPICYGOAT_PROTOCOL_H

#include <spicygoat/protocol/ProtocolState.h>
#include <spicygoat/protocol/packets.h>

namespace Protocol {
inline static constexpr const char *const PROTOCOL_VERSION_NAME = "1.20-pre1";
inline static const int PROTOCOL_VERSION_NUMBER = 134;
inline static const bool PROTOCOL_SNAPSHOT = true;
}  // namespace Protocol

#endif  // SPICYGOAT_PROTOCOL_H
