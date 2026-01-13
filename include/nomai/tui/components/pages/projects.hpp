#pragma once

#include <memory>
#include <ftxui/component/component.hpp>

#include "nomai/tui/tui.hpp"
#include "nomai/tui/components/page.hpp"
#include "nomai/core/nomai.hpp"

namespace nomai {
    
    class Tui;

    class ProjectsPage : public Page {
    public:
        ProjectsPage(Tui* tui, std::vector<Project> projects);

        ftxui::Component getMainComponent() override;
        ftxui::Component getSideComponent() override;
    
    private:
        Tui* tui;
        ftxui::Component menu;
        int selected = 0;

        std::vector<Project> projects;
        std::vector<std::string> projectNames;
    };
}