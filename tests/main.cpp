#include <iostream>
#include <filesystem>

#include "nomai/nomai.hpp"

int main(int argc, char* argv[])
{
    std::filesystem::path homeDir = std::getenv("HOME");
    nomai::App app(homeDir);
    app.config();

    return app.handleArguments(argc, argv);
}