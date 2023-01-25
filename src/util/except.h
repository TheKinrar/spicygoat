//
// Created by thekinrar on 25/01/23.
//

#pragma once

#include "stdexcept"

class protocol_error : public std::runtime_error {
   public:
    explicit protocol_error(const std::string& arg) : runtime_error(arg) {}
    explicit protocol_error(const char* string) : runtime_error(string) {}
};
