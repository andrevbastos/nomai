#include "nomai/tui/tui.hpp"

namespace nomai {
    using namespace ftxui;

    Tui::Tui() {
        loadProjects();
    }

    void Tui::run() {
        auto screen = ScreenInteractive::Fullscreen();

        int selected = 0;
        std::vector<std::string> entries = {
            "Dashboard",
            "Projetos",
            "Configurações",
        };
        
        auto menu = Menu(&entries, &selected);
        
        auto tab_dashboard = Renderer([] {
            return text("Aqui ficará o dashboard...") | center;
        });

        auto projectsList = Container::Vertical({});
        for (const auto& project : loadedProjects) {
            projectsList->Add(Renderer([project] {
                return hbox(
                    text(project.getName()) | flex,
                    text(project.getPath()) | dim | align_right
                );
            }));
        }
        
        auto tab_projects = Renderer([&] {
            return projectsList->Render();
        });

        auto tab_settings = Renderer([] {
            return text("Aqui ficarão as configurações...") | center;
        });

        auto tab_container = Container::Tab({
            tab_dashboard,
            tab_projects,
            tab_settings
        }, &selected);

        auto layout = Container::Horizontal({
            menu,
            tab_container,
        });

        auto renderer = Renderer(layout, [&] {    
            return vbox({
                text("NOMAI") | bold | hcenter,
                separator(),

                hbox({
                    menu->Render() | size(WIDTH, GREATER_THAN, 20),
                    separator(),
                    tab_container->Render() | flex
                }) | flex,

                separator(),
                text("v0.1.0 | Press 'q' to quit") | dim | hcenter
            });
        });

        auto final_component = Make<QuitHandler>(renderer, screen.ExitLoopClosure());

        screen.Loop(final_component);
    }

    void Tui::loadProjects() {
        loadedProjects = nomai::getRegisteredProjects();
    }
}