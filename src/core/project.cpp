#include "nomai/core/project.hpp"

namespace nomai {
    Project::Project(const std::string& name, const std::string& path, int rank, std::chrono::system_clock::time_point last_accessed, const std::string& ide, const std::vector<std::string>& auxApps)
        : name(name), path(path), ide(ide), auxApps(auxApps), rank(rank), last_accessed(last_accessed) {}

    bool Project::operator==(const Project& other) const {
        return name == other.name && path == other.path;
    }

    std::string Project::getName() const { return name; }
    std::string Project::getPath() const { return path; }
    std::string Project::getIde() const { return ide; }
    std::vector<std::string> Project::getAuxApps() const { return auxApps; }

    int Project::getRank() const { return rank; }
    void Project::setRank(int r) { rank = r; }
    std::chrono::system_clock::time_point Project::getLastAccess() const { return last_accessed; }
    void Project::updateLastAccess() { last_accessed = std::chrono::system_clock::now(); }
}