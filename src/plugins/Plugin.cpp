//
// Created by thekinrar on 06/04/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/plugins/Plugin.h>

void Plugin::runTask(const std::function<void()>& fn) {
    submitTask(std::make_shared<Task>(fn));
}

void Plugin::submitTask(const std::shared_ptr<Task>& task) {
    Server::get().getScheduler().submit(task);
    tasks.push_back(task);
}
