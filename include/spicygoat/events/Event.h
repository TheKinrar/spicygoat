//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include <functional>
#include <memory>

template <class E>
class Listener {
    std::function<void(E&)> callback;

   public:
    explicit Listener(const std::function<void(E&)>& callback) : callback(callback) {}

    void handle(E& event) {
        callback(event);
    };
};

template <class E>
class Event {
    static std::vector<std::weak_ptr<Listener<E>>> listeners;

   public:
    static void addListener(std::weak_ptr<Listener<E>> listener) {
        listeners.push_back(listener);
    }

    void call() {
        auto it = listeners.begin();
        while(it != listeners.end()) {
            auto locked = it->lock();
            if(locked) {
                locked->handle(*static_cast<E*>(this));
                ++it;
            } else {
                it = listeners.erase(it);
            }
        }
    }
};
