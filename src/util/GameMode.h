//
// Created by thekinrar on 09/01/23.
//

#pragma once

#include <stdexcept>

namespace GameMode {

enum class GameMode {
    Survival = 0,
    Creative = 1,
    Adventure = 2,
    Spectator = 3,
};

inline GameMode parse(int64_t gamemode) {
    if(gamemode < 0 || gamemode > 3)
        throw std::runtime_error("Invalid GameMode");

    return static_cast<GameMode>(gamemode);
}

}
