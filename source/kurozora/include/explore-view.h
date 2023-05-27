#pragma once

#include <gtkmm.h>

namespace kurozora
{
    class ExploreView : public Gtk::Box
    {
    public:
        ExploreView();
    public:
        std::shared_ptr<Gtk::Box> explore_main_box;
        std::shared_ptr<Gtk::Builder> builder;
    };
}