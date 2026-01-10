#pragma once

#include <functional>

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

class QuitHandler : public ComponentBase {
public:
    QuitHandler(Component child, std::function<void()> on_quit);

    bool OnEvent(Event event) override;

    Element Render() override;

private:
    Component child;
    std::function<void()> on_quit;
};