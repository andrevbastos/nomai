#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

#include "nomai/core/project.hpp"
#include "nomai/util/frecency.hpp"

using json = nlohmann::json;

TEST(CoreTest, ProjectSerialization) {
    auto now = std::chrono::system_clock::now();
    nomai::Project original("teste-json", "/tmp/teste", 100, now, "vim");

    json j = original;
    
    nomai::Project loaded = j.get<nomai::Project>();

    EXPECT_EQ(original.getName(), loaded.getName());
    EXPECT_EQ(original.getPath(), loaded.getPath());
    EXPECT_EQ(original.getRank(), loaded.getRank());
    
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(
        original.getLastAccess() - loaded.getLastAccess()
    );
    EXPECT_EQ(duration.count(), 0);
}

TEST(CoreTest, FrecencyDecayLogic) {
    std::vector<nomai::Project> projects;
    
    projects.emplace_back("proj-alto", "/path/1", 1000, std::chrono::system_clock::now(), "vim");
    projects.emplace_back("proj-medio", "/path/2", 100, std::chrono::system_clock::now(), "vim");
    projects.emplace_back("proj-baixo", "/path/3", 5, std::chrono::system_clock::now(), "vim");

    nomai::applyRankDecay(projects);

    EXPECT_EQ(projects[0].getRank(), 900);
    
    EXPECT_EQ(projects[1].getRank(), 90);
    
    EXPECT_EQ(projects[2].getRank(), 4);
}