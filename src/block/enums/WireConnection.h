//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include "../../util/Enum.h"

class WireConnection : public Enum {
    explicit WireConnection(const std::string& name) : Enum(name) {}

   public:
    static const WireConnection up, side, none;

    static const std::vector<WireConnection> values;
};

inline const WireConnection WireConnection::up = WireConnection("up");
inline const WireConnection WireConnection::side = WireConnection("side");
inline const WireConnection WireConnection::none = WireConnection("none");

inline const std::vector<WireConnection> WireConnection::values = {up, side, none};
