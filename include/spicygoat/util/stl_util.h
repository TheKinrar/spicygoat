//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <cstdlib>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace util {

template <class K, class V>
std::vector<V> extractMapValues(const std::unordered_map<K, V>& map) {
    std::vector<V> vec;
    for(const auto& item : map) {
        vec.push_back(item.second);
    }
    return vec;
}

template <class T>
std::vector<T> iotaVector(T min, size_t count) {
    std::vector<T> vec(count);
    std::iota(vec.begin(), vec.end(), min);
    return vec;
}

}  // namespace util
