#include <gtest/gtest.h>
#include "nomai/util/matcher.hpp"
#include "nomai/core/project.hpp"

TEST(MatcherTest, JaroWinklerDistance) {
    EXPECT_FLOAT_EQ(nomai::jaroWinklerDistance("nomai", "nomai"), 1.0f);
    
    EXPECT_FLOAT_EQ(nomai::jaroWinklerDistance("abc", "xyz"), 0.0f);
    
    float score = nomai::jaroWinklerDistance("martha", "marhta");
    EXPECT_GT(score, 0.9f);
    EXPECT_LT(score, 1.0f);
}

TEST(MatcherTest, ClosestMatchSelection) {
    std::vector<nomai::Project> projects = {
        nomai::Project("backend-api", "/tmp/backend", 0, std::chrono::system_clock::now(), "nvim"),
        nomai::Project("frontend-web", "/tmp/frontend", 0, std::chrono::system_clock::now(), "code"),
        nomai::Project("data-science", "/tmp/data", 0, std::chrono::system_clock::now(), "pycharm")
    };

    EXPECT_EQ(nomai::closestNameMatch("backend-api", projects), projects[0]);

    EXPECT_EQ(nomai::closestNameMatch("back", projects), projects[0]);
    
    EXPECT_EQ(nomai::closestNameMatch("web", projects), projects[1]);

    EXPECT_EQ(nomai::closestNameMatch("sci", projects), projects[2]);
}