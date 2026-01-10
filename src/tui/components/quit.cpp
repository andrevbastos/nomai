#include "nomai/tui/components/quit.hpp"

QuitHandler::QuitHandler(Component child, std::function<void()> on_quit) 
    : child(child), on_quit(on_quit) {
    Add(child);
}

bool QuitHandler::OnEvent(Event event) {
    if (child->OnEvent(event)) {
        return true;
    }

    if (event == Event::Character('q')) {
        on_quit();
        return true;
    }

    return false;
}

Element QuitHandler::Render() {
    return child->Render();
}