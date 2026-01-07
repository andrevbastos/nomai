#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "core/nomai.hpp"
#include "core/project.hpp"

bool handleArguments(int argc, char* argv[]);
bool isFlag(const char* arg);

int main(int argc, char* argv[]) {
    handleArguments(argc, argv);
    
    return 0;
}

bool handleArguments(int argc, char* argv[]) {
    namespace fs = std::filesystem;

    if (argc >= 1) {
        std::vector<std::string> flags;
        fs::path target = "";

        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);

            if (isFlag(argv[i])) {
                flags.push_back(arg);
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
            if (flag == "-h" || flag == "--help") {
                std::cout << "-v : Get current version." << std::endl;
                return 0;

            } else if (flag == "-v" || flag == "--version") {
                std::cout << "Version 1.0.0" << std::endl;
                return 0;

            } else if (flag == "-s" || flag == "--setup") {
                nomai::setup();
                return 0;

            } else if (flag == "-a" || flag == "--add") {
                if (target.empty()) {
                    std::cout << "Error: No target specified for registration." << std::endl;
                    return 1;
                }

                if (!target.has_filename()) {
                    target = target.parent_path();
                }
                nomai::Project newProject(target.filename().string(), target.string(), "default_ide");
                
                if (nomai::registerProject(newProject)) {
                    std::cout << "Project registered successfully: " << target << std::endl;
                    return 0;
                } else {
                    std::cout << "Failed to register project: " << target << std::endl;
                    return 1;
                }

            } else if (flag == "-b" || flag == "--batch") {
                if (target.empty()) {
                    std::cout << "Error: No target directory specified for recursive registration." << std::endl;
                    return 1;
                }

                if (!fs::is_directory(target)) {
                    std::cout << "Error: Target is not a directory: " << target << std::endl;
                    return 1;
                }

                for (auto entry : fs::directory_iterator(target)) {
                    if (entry.is_directory()) {
                        nomai::Project newProject(entry.path().filename().string(), entry.path().string(), "default_ide");
                        if (nomai::registerProject(newProject)) {
                            std::cout << "Project registered successfully: " << entry.path() << std::endl;
                        } else {
                            std::cout << "Failed to register project: " << entry.path() << std::endl;
                        }
                    }
                }
                return 0;

            } else if (flag == "-r" || flag == "--remove") {
                if (target.empty()) {
                    std::cout << "Error: No target specified for removal." << std::endl;
                    return 1;
                }

                if (!target.has_filename()) {
                    target = target.parent_path();
                }

                if (nomai::removeProject(target.string())) {
                    std::cout << "Project removed successfully: " << target << std::endl;
                    return 0;
                } else {
                    std::cout << "Failed to remove project: " << target << std::endl;
                    return 1;
                }
                return 1;
            } else {
                std::cout << "Unknown flag: " << flag << std::endl;
                return 1;
            }
        }
    }
    
    return 0;
};

bool isFlag(const char* arg)
{
    std::string strArg(arg);
    return strArg.rfind("-", 0) == 0;
};