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
        Glib::RefPtr<Gtk::Application> application;
        Glib::RefPtr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::Box> window;
    };
}