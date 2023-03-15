//
// Created by thekinrar on 14/03/23.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Plugin.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class PluginManager {
    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("PluginManager");
    std::unordered_map<std::string, std::unique_ptr<Plugin>> plugins;

   public:
    void loadPlugins();
};
