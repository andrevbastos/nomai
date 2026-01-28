#pragma once

#include <string>
#include <vector>
#include <cmath>

#include "nomai/core/project.hpp"

namespace nomai {
    Project closestNameMatch(const std::string& target, std::vector<Project>);
    Project closestPathMatch(const std::string& target, std::vector<Project>);

    float jaroDistance(const std::string& s1, const std::string& s2);
    float jaroWinklerDistance(const std::string& s1, const std::string& s2);
}