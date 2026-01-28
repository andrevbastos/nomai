#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "nomai/core/project.hpp"

namespace nomai {
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    void setup();

    bool registerProject(const Project& project);
    bool removeProject(const std::string& projectPath);
    bool updateRegisteredProject(const Project& project);
    bool updateAllRegisteredProjects(const std::vector<Project>& projects);
    
    bool runProjectWorkspace(const Project& project);
    
    std::vector<Project> getRegisteredProjects();
}

