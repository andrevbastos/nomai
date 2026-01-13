#pragma once

#include <memory>
#include "ftxui/component/component.hpp"
#include "nomai/tui/components/page.hpp"

namespace nomai {
    
    class Tui;

    class MainMenuPage : public Page {
    public:
        MainMenuPage(Tui* tui);

        ftxui::Component getMainComponent() override;
        ftxui::Component getSideComponent() override;
    
    private:
        Tui* tui;
        ftxui::Component menu;
        int selected = 0;
    };
}