//
// Created by thekinrar on 18/03/23.
//

#pragma once

#include <functional>

class Task {
    std::function<void()> callback;

   public:
    explicit Task(const std::function<void()>& callback) : callback(callback) {}

    void run() {
        callback();
    }
};
