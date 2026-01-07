#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "project.hpp"

namespace nomai {
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    inline fs::path getRegistryPath() {
        return fs::path(getenv("HOME")) / ".nomai" / "registry.json";
    }

    void setup() {
        std::cout << "[Nomai] Initializing setup..." << std::endl;
        fs::path home = fs::path(getenv("HOME"));
        fs::path corePath = home / ".nomai";
        fs::path registryPath = getRegistryPath();
        
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
    }

    bool registerProject(const Project& project) {
        fs::path registryPath = getRegistryPath();
        json registryJson;
        
        if (fs::exists(registryPath)) {
            std::ifstream registryFile(registryPath);
            try {
                registryFile >> registryJson;
            } catch (json::parse_error& e) {
                std::cerr << "[Error] Corrupted registry. Resetting..." << std::endl;
                registryJson = json::array();
            }
        } else {
            registryJson = json::array();
        }

        if (!registryJson.is_array()) {
            registryJson = json::array();
        }

        auto projectsVector = registryJson.get<std::vector<Project>>();

        fs::path newPath = fs::path(project.getPath()).lexically_normal();

        for (const auto& existingProject : projectsVector) {
            fs::path existingPath = fs::path(existingProject.getPath()).lexically_normal();
            
            if (existingPath == newPath) {
                std::cout << "[Info] Project already registered: " << project.getPath() << std::endl;
                return false;
            }
        }

        projectsVector.push_back(project);
        
        std::ofstream outFile(registryPath);
        json outJson = projectsVector;
        outFile << outJson.dump(4);
        
        return true;
    }

    bool removeProject(const std::string& projectPath) {
        fs::path registryPath = getRegistryPath();
        json registryJson;
        
        if (!fs::exists(registryPath)) {
            std::cerr << "[Error] Registry file does not exist." << std::endl;
            return false;
        }

        std::ifstream registryFile(registryPath);
        try {
            registryFile >> registryJson;
        } catch (json::parse_error& e) {
            std::cerr << "[Error] Corrupted registry." << std::endl;
            return false;
        }

        if (!registryJson.is_array()) {
            std::cerr << "[Error] Invalid registry format." << std::endl;
            return false;
        }

        auto projectsVector = registryJson.get<std::vector<Project>>();
        fs::path targetPath = fs::path(projectPath).lexically_normal();
        bool found = false;

        projectsVector.erase(
            std::remove_if(projectsVector.begin(), projectsVector.end(),
                [&](const Project& proj) {
                    fs::path existingPath = fs::path(proj.getPath()).lexically_normal();
                    if (existingPath == targetPath) {
                        found = true;
                        return true;
                    }
                    return false;
                }),
            projectsVector.end()
        );

        if (!found) {
            std::cout << "[Info] Project not found in registry: " << projectPath << std::endl;
            return false;
        }

        std::ofstream outFile(registryPath);
        json outJson = projectsVector;
        outFile << outJson.dump(4);
        
        return true;
    }
}

