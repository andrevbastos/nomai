#pragma once

#include <cmath>

#include "nomai/core/nomai.hpp"

namespace nomai {
    void rankUpProject(const Project& project);
    std::vector<Project> applyRankDecay(std::vector<Project>& projects);
    void balanceProjectRanks();
}