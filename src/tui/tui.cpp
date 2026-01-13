#include "nomai/tui/tui.hpp"

namespace nomai {
    using namespace ftxui;

    Tui::Tui() {
        loadProjects();
        initPages();
        
        pushPage(PageType::MAIN_MENU);
    }

    void Tui::setSelectedProjectIndex(int index) {
        selectedProjectIndex = index;
    }

    void Tui::initPages() {
        pages[PageType::MAIN_MENU] = std::make_shared<MainMenuPage>(this);
        pages[PageType::PROJECTS] = std::make_shared<ProjectsPage>(this, loadedProjects);
    }

    void Tui::pushPage(PageType type) {
        if (pages.find(type) == pages.end()) return;

        auto novaPagina = pages[type];
        if (!pageStack.empty() && pageStack.back() == novaPagina) return;

        pageStack.push_back(novaPagina);
        refreshLayout();
    }

    void Tui::popPage() {
        if (pageStack.size() > 1) {
            pageStack.pop_back();
            refreshLayout();
        }
    }

    void Tui::refreshLayout() {
        if (pageStack.empty()) return;

        Component left_panel;
        Component right_panel;

        if (pageStack.size() == 1) {
            active_panel_index = 0; 

            left_panel = pageStack.back()->getSideComponent();
            right_panel = Renderer([]{ 
                return vbox({
                    text(" NOMAI ") | bold | center,
                    text(" v0.1 ") | center
                }); 
            });
        } 
        else {
            active_panel_index = 1;

            auto prev_page = pageStack[pageStack.size() - 2];
            auto curr_page = pageStack.back();

            left_panel = CatchEvent(prev_page->getSideComponent(), [this](Event event) {
                if (event == Event::ArrowLeft) {
                    this->popPage();
                    return true;
                }
                return false;
            });

            right_panel = curr_page->getMainComponent();
        }

        auto split = Container::Horizontal({
            left_panel | size(WIDTH, GREATER_THAN, 25),
            right_panel | flex
        }, &active_panel_index);

        main_container = CatchEvent(split, [this](Event event) {
            if (event == Event::Escape) {
                if (pageStack.size() > 1) {
                    this->popPage();
                    return true;
                }
                screen.ExitLoopClosure()();
                return true;
            }
            return false;
        });
        
        main_container = Renderer(main_container, [=, this] {
            return vbox({
                text("Nomai Manager") | bold | hcenter,
                separator(),
                hbox({
                    left_panel->Render(),
                    separator(),
                    right_panel->Render() | flex
                }) | flex
            });
        });
    }

    void Tui::run() {
        auto global_renderer = Renderer([&] { 
            return main_container->Render(); 
        });
        
        auto global_handler = CatchEvent(global_renderer, [&](Event event) {
            return main_container->OnEvent(event);
        });

        auto final_component = Make<QuitHandler>(global_handler, screen.ExitLoopClosure());

        screen.Loop(final_component);
    }

    void Tui::loadProjects() {
        loadedProjects = nomai::getRegisteredProjects();
    }
}