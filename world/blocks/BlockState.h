//
// Created by thekinrar on 09/04/19.
//

#ifndef SPICYGOAT_BLOCKSTATE_H
#define SPICYGOAT_BLOCKSTATE_H


#include <string>
#include <cstdint>
#include <map>

class BlockState {
public:
    BlockState() = default;
    explicit BlockState(const std::string &name);

    void addProperty(const std::string& key, std::string value);

    const std::string &getName() const;

    bool operator<(const BlockState &rhs) const;

    bool operator>(const BlockState &rhs) const;

    bool operator<=(const BlockState &rhs) const;

    bool operator>=(const BlockState &rhs) const;

    std::string toString();

private:
    std::string name;

    std::map<std::string, std::string> properties;
};


#endif //SPICYGOAT_BLOCKSTATE_H
