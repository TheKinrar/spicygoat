//
// Created by thekinrar on 24/01/23.
//

#pragma once

namespace Reports {

nlohmann::ordered_json blocks() {
    nlohmann::ordered_json json;

    auto blocks = Server::get().getBlockRegistry().getBlocks();
    std::sort(blocks.begin(), blocks.end(), [](const std::reference_wrapper<Block>& a, const std::reference_wrapper<Block>& b) {
        return a.get().getName().getValue() < b.get().getName().getValue();
    });

    for(const auto &block : blocks) {
        nlohmann::ordered_json blockJson;

        auto properties = block.get().getProperties();
        std::sort(properties.begin(), properties.end(), [](const std::reference_wrapper<const Property>& a, const std::reference_wrapper<const Property>& b) {
            auto an = a.get().getName();
            auto bn = b.get().getName();

            if(an == "type" && bn != "type") return true;
            if(bn == "type" && an != "type") return false;
            return an < bn;
        });

        if(!properties.empty()) {
            nlohmann::ordered_json propertiesJson;
            for(const auto &property : properties) {
                std::vector<std::string> values;
                for(const auto &value : property.get().getValues()) {
                    values.push_back(value->toString());
                }
                propertiesJson[property.get().getName()] = values;
            }

            blockJson["properties"] = propertiesJson;
        }

        std::vector<nlohmann::ordered_json> statesJson;
        for(const auto &state : block.get().getStates()) {
            nlohmann::ordered_json stateJson;

            if(block.get().getDefaultState() == state) {
                stateJson["default"] = true;
            }

            stateJson["id"] = Server::get().getPalette()->getBlockStateId(state);

            if(!properties.empty()) {
                nlohmann::ordered_json propertiesJson;
                for(const auto &property : properties) {
                    propertiesJson[property.get().getName()] = state->getValue(property)->toString();
                }
                stateJson["properties"] = propertiesJson;
            }

            statesJson.push_back(stateJson);
        }
        blockJson["states"] = statesJson;

        json[block.get().getName().toString()] = blockJson;
    }

    return json;
}

}
