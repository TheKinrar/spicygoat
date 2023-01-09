//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <vector>

#include "../../entities/types/EntityPlayer.h"
#include "../Command.h"

class CommandGm : public Command {
   public:
    explicit CommandGm() : Command("gm") {}

    void run(const std::vector<std::string>& args, EntityPlayer& sender) override {
        if(args.size() == 1) {
            int val;
            try {
                val = std::stoi(args[0]);
            } catch(std::exception& e) {
                sender.sendMessage("§cBad value.");
                return;
            }

            if(val < 0 || val > 3) {
                sender.sendMessage("§cValue out of range.");
                return;
            }

            sender.setGamemode(static_cast<GameMode::GameMode>(val));
        }
    }
};
