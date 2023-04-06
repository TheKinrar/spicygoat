//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <absl/strings/str_split.h>
#include <spicygoat/commands/Command.h>
#include <spicygoat/entities/types/EntityPlayer.h>

class CommandEngine {
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;

   public:
    void registerCommand(std::unique_ptr<Command> command) {
        if(commands.contains(command->getName()))
            throw std::runtime_error("Command already exists");

        commands[command->getName()] = std::move(command);
    }

    void runCommand(const std::string& message, EntityPlayer& sender) {
        std::vector<std::string> args = absl::StrSplit(message, " ");
        std::string commandName = absl::AsciiStrToLower(args.front());
        args.erase(args.begin());

        auto it = commands.find(commandName);
        if(it == commands.end()) {
            sender.sendMessage("§cCommand not found.");
        } else {
            it->second->run(args, sender);
        }
    }
};
