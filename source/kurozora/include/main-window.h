#pragma once

#include <gtkmm.h>
#include <iostream>

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
        std::shared_ptr<Gtk::Box> window;
    };
}