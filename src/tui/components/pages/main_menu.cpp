#include "nomai/tui/components/pages/main_menu.hpp"
#include "nomai/tui/tui.hpp"

namespace nomai {
    using namespace ftxui;

    MainMenuPage::MainMenuPage(Tui* tui)
        : tui(tui) {
        
        static const std::vector<std::string> entries = {
            "Projetos",
            "Dashboard",
            "Configurações",
            "Sair"
        };
        
        auto option = MenuOption::Vertical();
        option.on_enter = [this] {
            if (selected == 0) {
                this->tui->pushPage(PageType::PROJECTS);
            } else if (selected == 1) {
                this->tui->pushPage(PageType::DASHBOARD);
            } else if (selected == 2) {
                this->tui->pushPage(PageType::SETTINGS);
            } else if (selected == 3) {
                // quit logic
            }
        };

        this->menu = Menu(&entries, &selected, option);
    }

    Component MainMenuPage::getMainComponent() {
        return Renderer(menu, [this] {
            return vbox({});
        });
    }

    Component MainMenuPage::getSideComponent() {
        return Renderer(menu, [this] {
            return vbox({
                menu->Render() | center
            });
        });
    }
}