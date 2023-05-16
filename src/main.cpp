#include <spicygoat/Server.h>
#include <spicygoat/TCPServer.h>

#include <CLI/CLI.hpp>
#include <csignal>

#include "reports/blocks.h"

static_assert(sizeof(float) == 4);
static_assert(sizeof(double) == 8);

void sigterm_handler(int) {
    TCPServer::get().stop();
}

void writeReport(const std::string& name, const nlohmann::ordered_json& report) {
    std::ofstream f("reports/" + name + ".json");
    f << report.dump(2);
}

int main(int argc, char** argv) {
#ifdef __linux__
    signal(SIGPIPE, SIG_IGN);
#endif
    signal(SIGTERM, sigterm_handler);

    CLI::App app{"SpicyGoat"};
    auto reports = app.add_flag("--reports", "Generate JSON reports");
    CLI11_PARSE(app, argc, argv);

    if(reports->count()) {
        spdlog::info("Generating reports");
        Server::get().load();

        std::filesystem::create_directory("reports");
        writeReport("blocks", Reports::blocks());

        spdlog::info("Done");
    } else {
        Server::get().run();
    }

    return 0;
}
