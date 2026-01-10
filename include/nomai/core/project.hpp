#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace nomai {
    class Project {
    public:
        Project() = default;
        Project(const std::string& name, const std::string& path, const std::string& ide, const std::vector<std::string>& auxApps = {});
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Project, name, path, ide, auxApps);

        std::string getName() const;
        std::string getPath() const;
        std::string getIde() const;
        std::vector<std::string> getAuxApps() const;

    private:
        std::string name;
        std::string path;
        std::string ide;
        std::vector<std::string> auxApps;
    };
}