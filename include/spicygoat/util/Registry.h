//
// Created by thekinrar on 04/01/23.
//

#ifndef SPICYGOAT_REGISTRY_H
#define SPICYGOAT_REGISTRY_H

#include <string>
#include <unordered_map>
#include <utility>

struct Registry {
    const std::string id;
    std::unordered_map<std::string, int32_t> keyToId;
    std::unordered_map<int32_t, std::string> idToKey;
    std::string defaultKey;

   public:
    explicit Registry(std::string id) : id(std::move(id)) {}
    Registry(const Registry&) = delete;

    virtual void addMapping(const std::string& key, int32_t id) {
        keyToId.emplace(key, id);
        idToKey.emplace(id, key);
    }

    bool containsId(int32_t id) const {
        return idToKey.contains(id);
    }

    int32_t getId(const std::string& key) const {
        return keyToId.at(key);
    }

    std::string getKey(int32_t id) const {
        return idToKey.at(id);
    }
};

#endif  // SPICYGOAT_REGISTRY_H
