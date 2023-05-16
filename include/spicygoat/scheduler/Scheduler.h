//
// Created by thekinrar on 18/03/23.
//

#pragma once

#include <spicygoat/scheduler/Task.h>

#include <memory>
#include <vector>

class Scheduler {
    std::vector<std::weak_ptr<Task>> tasks;

   public:
    void submit(const std::weak_ptr<Task>& task);

    void tick();
};
