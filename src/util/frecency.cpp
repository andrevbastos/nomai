#include "nomai/util/frecency.hpp"

namespace nomai {
    void rankUpProject(const Project& project) {
        if (project.getRank() >= 100) {
            balanceProjectRanks();
        }

        std::vector<Project> projects = getRegisteredProjects();
        
        for (auto& p : projects) {
            if (p.getPath() == project.getPath()) {
                p.setRank(p.getRank() + 10);
                p.updateLastAccess();
                break;
            }
        }

        updateAllRegisteredProjects(projects);
    };

    std::vector<Project> applyRankDecay(std::vector<Project>& projects) {
        if (projects.empty()) return projects;
        for (auto& p : projects) {
            p.setRank((int)std::floor(p.getRank() * 0.9));
        }
        return projects;
    }

    void balanceProjectRanks() {
        std::vector<Project> projects = getRegisteredProjects();
        projects = applyRankDecay(projects);
        updateAllRegisteredProjects(projects);
    }
}