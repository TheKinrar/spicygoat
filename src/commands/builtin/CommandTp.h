//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../Command.h"

class CommandTp : public Command {
   public:
    explicit CommandTp() : Command("tp") {}

    void run(const std::vector<std::string>& args, EntityPlayer& sender) override {
        if(args.size() == 1) {
            auto target = Server::get().getPlayer(args[0]);
            if(target.has_value()) {
                sender.teleport(target->get()->getLocation());
            } else {
                sender.sendMessage("§cTarget not found.");
            }
        } else if(args.size() == 3) {
            double x, y, z;
            try {
                x = std::stod(args[0]);
                y = std::stod(args[1]);
                z = std::stod(args[2]);
            } catch(std::exception& e) {
                sender.sendMessage("§cInvalid coordinates.");
                return;
            }
            sender.teleport(Location(x, y, z, sender.getLocation().getYaw(), sender.getLocation().getPitch()));
        }
    }
};
