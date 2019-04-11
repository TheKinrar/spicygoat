//
// Created by thekinrar on 09/04/19.
//

#ifndef SPICYGOAT_BLOCKSTATE_H
#define SPICYGOAT_BLOCKSTATE_H


#include <string>
#include <cstdint>

class BlockState {
public:
    BlockState(const std::string &name);

    const std::string &getName() const;

    bool operator<(const BlockState &rhs) const;

    bool operator>(const BlockState &rhs) const;

    bool operator<=(const BlockState &rhs) const;

    bool operator>=(const BlockState &rhs) const;

private:
    std::string name;
};


#endif //SPICYGOAT_BLOCKSTATE_H
