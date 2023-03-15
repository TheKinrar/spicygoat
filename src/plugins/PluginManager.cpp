//
// Created by thekinrar on 14/03/23.
//

#include "PluginManager.h"

#include <dlfcn.h>

#include <filesystem>

void PluginManager::loadPlugins() {
    for(const auto& file : std::filesystem::directory_iterator("plugins")) {
        if(file.is_regular_file() && file.path().filename().string().ends_with(".so")) {
            logger->info("Loading " + file.path().filename().string());

            void* handle = dlopen(file.path().c_str(), RTLD_LAZY | RTLD_GLOBAL);
            if(!handle) {
                logger->error("dlopen failed: {}", dlerror());
                std::exit(1);
            }

            std::unique_ptr<Plugin> (*sg_entry)();
            sg_entry = (std::unique_ptr<Plugin> (*)()) dlsym(handle, "sg_entry");
            if(!sg_entry) {
                logger->error("dlsym failed: {}", dlerror());
                std::exit(1);
            }

            auto ptr = sg_entry();
            auto& plugin = *ptr;
            plugins[ptr->getId()] = std::move(ptr);

            logger->info("Loaded {}", plugin.getId());
        }
    }
}
