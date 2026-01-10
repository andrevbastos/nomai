#include "nomai/core/project.hpp"

namespace nomai {
    Project::Project(const std::string& name, const std::string& path, const std::string& ide, const std::vector<std::string>& auxApps)
        : name(name), path(path), ide(ide), auxApps(auxApps) {}

    std::string Project::getName() const { return name; }
    std::string Project::getPath() const { return path; }
    std::string Project::getIde() const { return ide; }
    std::vector<std::string> Project::getAuxApps() const { return auxApps; }
}