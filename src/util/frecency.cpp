#include "nomai/util/frecency.hpp"

namespace nomai {
    void rankUpProject(const Project& project) {
        Project updatedProject = project;

        if (updatedProject.getRank() > 500) {
            balanceProjectRanks();
        }
        updatedProject.setRank(project.getRank() + 10);

        updateRegisteredProject(updatedProject);
    };

    void applyRankDecay(std::vector<Project>& projects) {
        if (projects.empty()) return;
        for (auto& p : projects) {
            p.setRank((int)std::floor(p.getRank() * 0.9));
        }
    }

    void balanceProjectRanks() {
        std::vector<Project> projects = getRegisteredProjects();
        applyRankDecay(projects);
        updateAllRegisteredProjects(projects);
    }
}