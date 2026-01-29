/*
TODO
    Projects TUI configuration
    Base project templates
    Projects tagging
    Process launcher
    Git context reader
    Bye messages
*/

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "nomai/core/nomai.hpp"
#include "nomai/core/project.hpp"
#include "nomai/tui/tui.hpp"
#include "nomai/util/matcher.hpp"
#include "nomai/util/frecency.hpp"

bool handleArguments(int argc, char* argv[]);
bool isFlag(const char* arg);
bool isDirectory(const std::string& target);
void setup();
void add(std::string target);
void batch(std::string target);
void remove(std::string target);
void cascade(std::string target);

int main(int argc, char* argv[]) {
    if (handleArguments(argc, argv)) {
        nomai::Tui app;
        app.run();
    }

    return 0;
}

bool handleArguments(int argc, char* argv[]) {
    namespace fs = std::filesystem;

    if (argc >= 1) {
        std::vector<std::string> flags;
        std::string target = "";

        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);

            if (isFlag(argv[i])) {
                flags.push_back(arg);
            } else {
                if (target.empty()) {
                    target = argv[i];
                } else {
                    std::cout << "Unexpected argument: " << argv[i] << std::endl;
                    return 0;
                }
            }
        }

        if (flags.empty()) {
            fs::path possiblePath(target);

            bool isPath = false;
            if (isDirectory(target) || (target.find(fs::path::preferred_separator) != std::string::npos || target.find('/') != std::string::npos) ) {
                isPath = true;
            }

            nomai::Project projectToRun;

            if (isPath) projectToRun = nomai::closestPathMatch(target, nomai::getRegisteredProjects());
            else projectToRun = nomai::closestNameMatch(target, nomai::getRegisteredProjects());
            
            nomai::rankUpProject(projectToRun);
            nomai::runProjectWorkspace(projectToRun);

            return 0;
        }

        for (const auto& flag : flags) {
            if (flag == "-h" || flag == "--help") {
                std::cout << "-h / --help: Show this help message." << std::endl;
                std::cout << "-v / --version: Get current version." << std::endl;
                std::cout << "-s / --setup: Setup nomai environment." << std::endl;
                std::cout << "-d / --default: Set default settings." << std::endl;
                std::cout << "-a / --add: Add a new project." << std::endl;
                std::cout << "-b / --batch: Recursively add all projects in a directory." << std::endl;
                std::cout << "-r / --remove: Remove a project." << std::endl;
                std::cout << "-c / --cascade: Recursively remove all projects in a directory." << std::endl;
            } else if (flag == "-s" || flag == "--setup") {
                setup();

            } else if (flag == "-d" || flag == "--default") {
                std::cout << "Set default setting." << std::endl;

            } else if (flag == "-a" || flag == "--add") {
                add(target);

            } else if (flag == "-b" || flag == "--batch") {
                batch(target);

            } else if (flag == "-r" || flag == "--remove") {
                remove(target);

            } else if (flag == "-c" || flag == "--cascade") {
                cascade(target);
                
            } else {
                std::cout << "Unknown flag: " << flag << std::endl;
            }
        }
    }

    return 0;
};

inline bool isFlag(const char* arg) {
    std::string strArg(arg);
    return strArg.rfind("-", 0) == 0;
};

inline bool isDirectory(const std::string& target) {
    return target.empty() || std::filesystem::is_directory(target);
};

void setup() {
    namespace fs = std::filesystem;

    std::cout << "[Nomai] Initializing setup..." << std::endl;
    fs::path home = fs::path(getenv("HOME"));
    fs::path corePath = home / ".nomai";
    fs::path registryPath = fs::path(getenv("HOME")) / ".nomai" / "registry.json";
    
    if (!fs::exists(corePath)) {
        fs::create_directory(corePath);
        std::cout << "[Info] Created core directory: " << corePath << std::endl;
    }

    if (!fs::exists(registryPath)) {
        std::ofstream newFile(registryPath);
        newFile << "[]"; 
        newFile.close();
        std::cout << "[Info] Created registry file: " << registryPath << std::endl;
    } else {
        std::ifstream file(registryPath);
        if (file.peek() == std::ifstream::traits_type::eof()) {
            std::ofstream fixFile(registryPath);
            fixFile << "[]";
        }
    }
    
    std::cout << "[Nomai] Setup completed." << std::endl;
};

void add(std::string target) {
    namespace fs = std::filesystem;

    if (!isDirectory(target)) {
        std::cout << "Error: No such directory." << target << std::endl;
        return;
    }

    fs::path targetPath(target);

    if (!targetPath.has_filename()) {
        targetPath = targetPath.parent_path();
    }
    nomai::Project newProject(targetPath.filename().string(), targetPath.string(), 50, std::chrono::system_clock::now(), "code");
    
    if (nomai::registerProject(newProject)) {
        std::cout << "Project registered successfully: " << target << std::endl;
    } else {
        std::cout << "Failed to register project: " << target << std::endl;
    }
};

void batch(std::string target) {
    namespace fs = std::filesystem;
    
    if (!isDirectory(target)) {
        std::cout << "Error: No such directory." << target << std::endl;
        return;
    }

    for (auto entry : fs::directory_iterator(target)) {
        if (entry.is_directory()) {
            nomai::Project newProject(entry.path().filename().string(), entry.path().string(), 50, std::chrono::system_clock::now(), "code");
            if (nomai::registerProject(newProject)) {
                std::cout << "Project registered successfully: " << entry.path() << std::endl;
            } else {
                std::cout << "Failed to register project: " << entry.path() << std::endl;
            }
        }
    }
};

void remove(std::string target) {
    namespace fs = std::filesystem;

    if (!isDirectory(target)) {
        std::cout << "Error: No such directory." << target << std::endl;
        return;
    }

    fs::path targetPath(target);
    if (!targetPath.has_filename()) {
        targetPath = targetPath.parent_path();
    }

    if (nomai::removeProject(targetPath.string())) {
        std::cout << "Project removed successfully: " << target << std::endl;
    } else {
        std::cout << "Failed to remove project: " << target << std::endl;
    }
};

void cascade(std::string target) {
    namespace fs = std::filesystem;

    if (!isDirectory(target)) {
        std::cout << "Error: No such directory." << target << std::endl;
        return;
    }

    fs::path targetPath(target);

    if (!targetPath.has_filename()) {
        targetPath = targetPath.parent_path();
    }

    for (auto entry : fs::directory_iterator(target)) {
        if (entry.is_directory()) {
            if (nomai::removeProject(entry.path().string())) {
                std::cout << "Project removed successfully: " << entry.path() << std::endl;
            } else {
                std::cout << "Failed to remove project: " << entry.path() << std::endl;
            }
        }
    }
};