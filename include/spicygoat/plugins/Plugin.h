//
// Created by thekinrar on 14/03/23.
//

#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spicygoat/events/Event.h>
#include <spicygoat/scheduler/Task.h>

#include <string>
#include <utility>

class Plugin {
    const std::string id;
    std::shared_ptr<spdlog::logger> logger;

    std::vector<std::shared_ptr<void>> listeners;
    std::vector<std::shared_ptr<void>> tasks;

   public:
    explicit Plugin(std::string id) : id(std::move(id)) {
        logger = spdlog::get(getId());
        if(!logger) logger = spdlog::stdout_color_mt(getId());
    }

    [[nodiscard]]
    const std::string& getId() const {
        return id;
    }

    [[nodiscard]]
    const std::shared_ptr<spdlog::logger>& getLogger() const {
        return logger;
    }

    template <class E>
    void listen(const std::function<void(E&)>& callback) {
        auto listener = std::make_shared<Listener<E>>(callback);
        E::addListener(listener);
        listeners.push_back(listener);
    }

    void runTask(const std::function<void()>& task);
    void submitTask(const std::shared_ptr<Task>& task);
};
