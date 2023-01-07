//
// Created by thekinrar on 03/01/23.
//

#ifndef SPICYGOAT_ITEMSTACK_H
#define SPICYGOAT_ITEMSTACK_H

#include <nbt_tags.h>

#include <cstdint>

struct ItemStack {
    bool present;
    int32_t id;
    int8_t count;
    bool hasNbt;
    std::shared_ptr<nbt::tag_compound> nbt;

    ItemStack() : present(false), id(0), count(0), hasNbt(false) {}

    explicit ItemStack(int32_t id, int8_t count = 1) : present(true), id(id), count(count), hasNbt(false) {}

    ItemStack(int32_t id, int8_t count, const std::shared_ptr<nbt::tag_compound> &nbt)
        : present(true), id(id), count(count), hasNbt(true), nbt(nbt) {}
};

#endif  // SPICYGOAT_ITEMSTACK_H
