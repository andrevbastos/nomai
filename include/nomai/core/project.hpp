#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <nlohmann/json.hpp>

namespace nlohmann {
    template <>
    struct adl_serializer<std::chrono::system_clock::time_point> {
        static void to_json(json& j, const std::chrono::system_clock::time_point& tp) {
            j = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
        }

        static void from_json(const json& j, std::chrono::system_clock::time_point& tp) {
            if (j.is_number()) {
                tp = std::chrono::system_clock::time_point(std::chrono::seconds(j.get<long long>()));
            } else {
                tp = std::chrono::system_clock::now();
            }
        }
    };
}

namespace nomai {
    class Project {
    public:
        Project() = default;
        Project(const std::string& name, const std::string& path, int rank, std::chrono::system_clock::time_point last_accessed, const std::string& ide, const std::vector<std::string>& auxApps = {});
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Project, name, path, rank, last_accessed, ide, auxApps);

        std::string getName() const;
        std::string getPath() const;
        std::string getIde() const;
        std::vector<std::string> getAuxApps() const;

        int getRank() const;
        void setRank(int r);

        std::chrono::system_clock::time_point getLastAccess() const;
        void updateLastAccess();

        bool operator==(const Project& other) const;
        
    private:
        std::string name;
        std::string path;
        std::string ide;
        std::vector<std::string> auxApps;

        int rank;
        std::chrono::system_clock::time_point last_accessed;
    };
}