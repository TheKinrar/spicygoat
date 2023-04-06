//
// Created by thekinrar on 31/01/23.
//

#pragma once

#include <random>

class Random {
    std::mt19937 engine;

   public:
    Random() : engine(std::random_device()()) {}

    static Random& get() {
        static Random i{};
        return i;
    }

    double nextDouble() {
        return std::uniform_real_distribution()(engine);
    }
};
