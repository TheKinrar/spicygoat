//
// Created by thekinrar on 18/03/23.
//

#pragma once

#include <memory>
#include <vector>

#include <spicygoat/scheduler/Task.h>

class Scheduler {
    std::vector<std::weak_ptr<Task>> tasks;

   public:
    void submit(const std::weak_ptr<Task>& task);

    void tick();
};
