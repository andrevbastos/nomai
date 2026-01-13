#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace nomai {
    class Page {
    public:
        virtual ~Page() = default;

        virtual ftxui::Component getSideComponent() = 0;
        virtual ftxui::Component getMainComponent() = 0;

    protected:
        ftxui::Component side;
        ftxui::Component main;
    };
}