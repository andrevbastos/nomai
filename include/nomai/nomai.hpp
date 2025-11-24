#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace nomai {
    class App {
    public:
        App(const std::filesystem::path& homeDir);
        bool handleArguments(int argc, char* argv[]);
        void config();

    private:
        bool isFlag(const char* arg);
        void add(const std::filesystem::path& target);
        void addAll(const std::filesystem::path& target);
        void clean();

        std::filesystem::path configPath;
    };
}