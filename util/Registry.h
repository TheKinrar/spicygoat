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
    std::unordered_map<std::string, int32_t> entries;
    std::unordered_map<int32_t, std::string> entriesR;
    std::string defaultEntry;

    explicit Registry(std::string id) : id(std::move(id)) {}
};


#endif //SPICYGOAT_REGISTRY_H
