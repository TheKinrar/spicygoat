//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <vector>

#include <spicygoat/commands/Command.h>
#include <spicygoat/entities/types/EntityPlayer.h>

class CommandSpeed : public Command {
   public:
    explicit CommandSpeed() : Command("speed") {}

    void run(const std::vector<std::string>& args, EntityPlayer& sender) override {
        if(args.size() == 1) {
            int val;
            try {
                val = std::stoi(args[0]);
            } catch(std::exception& e) {
                sender.sendMessage("§cBad value.");
                return;
            }

            if(val > 10) {
                sender.sendMessage("§cValue too high.");
                return;
            }

            sender.setFlyingSpeed((float) val * 0.05f);
        }
    }
};
