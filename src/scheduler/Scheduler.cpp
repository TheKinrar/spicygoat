//
// Created by thekinrar on 18/03/23.
//

#include <spicygoat/scheduler/Scheduler.h>

void Scheduler::submit(const std::weak_ptr<Task>& task) {
    tasks.push_back(task);
}

void Scheduler::tick() {
    auto it = tasks.begin();
    while(it != tasks.end()) {
        auto locked = it->lock();
        if(locked) {
            locked->run();
            ++it;
        } else {
            it = tasks.erase(it);
        }
    }
}
