#include "nomai/core/nomai.hpp"

namespace nomai {
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    inline fs::path getRegistryPath() {
        return fs::path(getenv("HOME")) / ".nomai" / "registry.json";
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
                return 0;
            }
        }

        projectsVector.push_back(project);
        
        std::ofstream outFile(registryPath);
        json outJson = projectsVector;
        outFile << outJson.dump(4);
        
        return 1;
    }

    bool removeProject(const std::string& projectPath) {
        fs::path registryPath = getRegistryPath();
        json registryJson;
        
        if (!fs::exists(registryPath)) {
            std::cerr << "[Error] Registry file does not exist." << std::endl;
            return 0;
        }

        std::ifstream registryFile(registryPath);
        try {
            registryFile >> registryJson;
        } catch (json::parse_error& e) {
            std::cerr << "[Error] Corrupted registry." << std::endl;
            return 0;
        }

        if (!registryJson.is_array()) {
            std::cerr << "[Error] Invalid registry format." << std::endl;
            return 0;
        }

        auto projectsVector = registryJson.get<std::vector<Project>>();
        fs::path targetPath = fs::path(projectPath).lexically_normal();
        bool found = 0;

        projectsVector.erase(
            std::remove_if(projectsVector.begin(), projectsVector.end(),
                [&](const Project& proj) {
                    fs::path existingPath = fs::path(proj.getPath()).lexically_normal();
                    if (existingPath == targetPath) {
                        found = 1;
                        return 1;
                    }
                    return 0;
                }),
            projectsVector.end()
        );

        if (!found) {
            std::cout << "[Info] Project not found in registry: " << projectPath << std::endl;
            return 0;
        }

        std::ofstream outFile(registryPath);
        json outJson = projectsVector;
        outFile << outJson.dump(4);
        
        return 1;
    }

    bool updateRegisteredProject(const Project& project) {
        fs::path registryPath = getRegistryPath();
        json registryJson;
        
        if (!fs::exists(registryPath)) {
            std::cerr << "[Error] Registry file does not exist." << std::endl;
            return 0;
        }

        std::ifstream registryFile(registryPath);
        try {
            registryFile >> registryJson;
        } catch (json::parse_error& e) {
            std::cerr << "[Error] Corrupted registry." << std::endl;
            return 0;
        }

        if (!registryJson.is_array()) {
            std::cerr << "[Error] Invalid registry format." << std::endl;
            return 0;
        }

        auto projectsVector = registryJson.get<std::vector<Project>>();
        fs::path targetPath = fs::path(project.getPath()).lexically_normal();
        bool found = 0;

        for (auto& existingProject : projectsVector) {
            fs::path existingPath = fs::path(existingProject.getPath()).lexically_normal();
            if (existingPath == targetPath) {
                existingProject = project;
                found = 1;
                break;
            }
        }

        if (!found) {
            std::cout << "[Info] Project not found in registry: " << project.getPath() << std::endl;
            return 0;
        }

        std::ofstream outFile(registryPath);
        json outJson = projectsVector;
        outFile << outJson.dump(4);
        
        return 1;
    }

    bool updateAllRegisteredProjects(const std::vector<Project>& projects) {
        fs::path registryPath = getRegistryPath();
        
        if (!fs::exists(registryPath)) {
            std::cerr << "[Error] Registry file does not exist." << std::endl;
            return 0;
        }

        std::ofstream outFile(registryPath);
        json outJson = projects;
        outFile << outJson.dump(4);
        
        return 1;
    }

    bool runProjectWorkspace(const Project& project) {
        std::string path = project.getPath();
        std::string ide = project.getIde();
        std::vector<std::string> auxApps = project.getAuxApps();

        if (ide.empty() || path.empty()) {
            std::cerr << "[Error] IDE or project path is empty." << std::endl;
            return 0;
        }

        std::string command = ide + " " + path + " &";
        int result = system(command.c_str());

        if (result != 0) {
            std::cerr << "[Error] Failed to launch IDE: " << ide << std::endl;
            return 0;
        }

        if (!auxApps.empty()) {
            for (const auto& auxApp : auxApps) {
                std::string auxCommand = auxApp + " " + path + " &";
                int result = system(auxCommand.c_str());
                if (result != 0) {
                    std::cerr << "[Error] Failed to launch Auxiliar App: " << auxApp << std::endl;
                    return 0;
                }
            }
        }

        return 1;
    }

    std::vector<Project> getRegisteredProjects() {
        fs::path registryPath = getRegistryPath();
        json registryJson;
        std::vector<Project> projectsVector;

        if (!fs::exists(registryPath)) {
            std::cerr << "[Error] Registry file does not exist." << std::endl;
            return projectsVector;
        }

        std::ifstream registryFile(registryPath);
        try {
            registryFile >> registryJson;
        } catch (json::parse_error& e) {
            std::cerr << "[Error] Corrupted registry." << std::endl;
            return projectsVector;
        }

        if (!registryJson.is_array()) {
            std::cerr << "[Error] Invalid registry format." << std::endl;
            return projectsVector;
        }

        projectsVector = registryJson.get<std::vector<Project>>();
        return projectsVector;
    }
}
