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

    static void call(E& event) {
        auto it = listeners.begin();
        while(it != listeners.end()) {
            auto locked = it->lock();
            if(locked) {
                locked->handle(event);
                ++it;
            } else {
                it = listeners.erase(it);
            }
        }
    }
};
