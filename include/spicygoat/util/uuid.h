//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <uuid.h>

namespace uuids {

inline uuid generate() {
    std::random_device rd;
    std::array<int, std::mt19937::state_size> seed_data{};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{generator};
    return gen();
}

}  // namespace uuids
