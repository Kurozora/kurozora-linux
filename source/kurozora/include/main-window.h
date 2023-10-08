#pragma once

#include <gtkmm.h>
#include <iostream>
#include "../src/views/explore-view.h"

namespace kurozora
{
    class MainWindow : public Gtk::Window
    {
    public:
        MainWindow();
        ~MainWindow();
    public:
        std::shared_ptr<Gtk::Application> application;
        std::shared_ptr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::CssProvider> css_provider;
        std::shared_ptr<Gtk::Box> main_box;

        std::unique_ptr<ExploreView> explore_view;
    };
}