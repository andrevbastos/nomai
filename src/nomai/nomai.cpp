#include "nomai/nomai.hpp"

namespace nomai {
    App::App(const std::filesystem::path& homeDir)
        : configPath(homeDir / ".config" / "nomai")
    {};

    bool App::handleArguments(int argc, char* argv[])
    {
        if (argc >= 1) {
            std::vector<std::string> flags;
            fs::path target = "";

            for (int i = 1; i < argc; ++i) {
                std::string flag(argv[i]);

                if (isFlag(argv[i])) {
                    flags.push_back(flag);
                } else {
                    if (target.empty()) {
                        target = fs::path(argv[i]);
                    } else {
                        std::cout << "Unexpected argument: " << argv[i] << std::endl;
                        return 1;
                    }
                }
            }

            for (const auto& flag : flags) {
                if (flag == "-a" || flag == "--add") {
                    if (target.empty()) {
                        std::cout << "--add requires a target path." << std::endl;
                        return 1;
                    }
                    add(target);
                } else if (flag == "-r" || flag == "--recursive") {
                    if (target.empty()) {
                        std::cout << "-r requires a target path." << std::endl;
                        return 1;
                    }
                    addAll(target);
                } else if (flag == "-c" || flag == "--clean") {
                    clean();
                } else {
                    std::cout << "Unknown flag: " << flag << std::endl;
                    return 1;
                }
            }
        }
        
        return 0;
    };

    void App::config()
    {
        if (!fs::exists(configPath)) {
            fs::create_directories(configPath);
        }
    };

    void App::add(const std::filesystem::path& target)
    {
        std::filesystem::path absPath = std::filesystem::absolute(target);
        std::filesystem::path linkPath = configPath / target.filename();

        if (!std::filesystem::exists(linkPath)) {
            std::filesystem::create_symlink(absPath, linkPath);
            std::cout << "Linked: " << target.filename() << std::endl;
        } else {
            std::cout << "Link already exists: " << target.filename() << std::endl;
        }
    };

    void App::addAll(const std::filesystem::path& target)
    {
        for (auto d : fs::directory_iterator(target)) {
            if (d.is_directory()) {
                fs::path absPath = fs::absolute(d.path());
                fs::path linkPath = configPath / d.path().filename();
                
                if (!fs::exists(linkPath)) {
                    fs::create_directory_symlink(absPath, linkPath);
                    std::cout << "Linked: " << d.path().filename() << std::endl;
                }
            }
        }
        std::cout << "Recursive add complete." << std::endl;
    };

    void App::clean()
    {
        fs::remove_all(configPath);
        std::cout << "Cleaned up config." << std::endl;
    };

    bool App::isFlag(const char* arg)
    {
        std::string strArg(arg);
        return strArg.rfind("-", 0) == 0;
    };
};