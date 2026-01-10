#pragma once

#include <vector>
#include <list>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "nomai/core/nomai.hpp"
#include "nomai/tui/components/quit.hpp"
#include "nomai/core/project.hpp"

namespace ftxui {
    class ComponentBase;
}

namespace nomai {

    class Tui {
    public:
        Tui(); 
        ~Tui() = default;

        void run();

    private:
        std::vector<Project> loadedProjects;

        void loadProjects();
    };

}