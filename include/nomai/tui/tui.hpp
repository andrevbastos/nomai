#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <memory>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "nomai/tui/components/pages/main_menu.hpp"
#include "nomai/tui/components/pages/projects.hpp"
#include "nomai/tui/components/quit.hpp"
#include "nomai/core/nomai.hpp"

namespace nomai {
    
    class Page;

    enum PageType {
        MAIN_MENU,
        DASHBOARD,
        PROJECTS,
        SETTINGS,
        QUIT,
        PROJECT_DETAILS
    };

    class Tui {
    public:
        Tui(); 
        ~Tui() = default;

        void run();
        void pushPage(PageType type);
        void popPage();

        void setSelectedProjectIndex(int index);

    private:
        std::vector<Project> loadedProjects;
        int selectedProjectIndex = -1;
        
        std::unordered_map<PageType, std::shared_ptr<Page>> pages;
        std::vector<std::shared_ptr<Page>> pageStack;
        int active_panel_index = 0;

        ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
        ftxui::Component main_container;
    
        void refreshLayout();
        void loadProjects();
        void initPages();
    };
}