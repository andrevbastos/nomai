#include "nomai/tui/components/pages/projects.hpp"

namespace nomai {
    using namespace ftxui;

    ProjectsPage::ProjectsPage(Tui* tui, std::vector<Project> projects)
        : tui(tui), projects(projects) {
        
        this->projectNames.clear(); 
        for (const auto& project : projects) {
            this->projectNames.push_back(project.getName());
        }

        auto option = MenuOption::Vertical();
        option.on_enter = [this, projects, tui] {
            if (selected >= 0 && selected < static_cast<int>(projects.size())) {
                tui->pushPage(PageType::PROJECT_DETAILS);
                tui->setSelectedProjectIndex(selected);
            }
        };

        this->menu = Menu(&this->projectNames, &selected, option);
    }

    Component ProjectsPage::getMainComponent() {
        return Renderer(menu, [this] {
            return vbox({
                menu->Render() | center
            });
        });
    }

    Component ProjectsPage::getSideComponent() {
        return Renderer(menu, [this] {
            return vbox({
                menu->Render() | center
            });
        });
    }
}