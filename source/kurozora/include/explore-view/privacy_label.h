#pragma once

#include <gtkmm.h>

namespace kurozora
{
    class PrivacyLabel
    {
    public:
        PrivacyLabel(Gtk::Window* parent, std::shared_ptr<Gtk::Builder> builder, const std::string&& label_id);
    public:
        std::unique_ptr<Gtk::Label> label;
        std::shared_ptr<Gtk::GestureClick> gesture_click;
        std::unique_ptr<Gtk::Window> popup_window;
        std::unique_ptr<Gtk::TextView> popup_text;
        std::shared_ptr<Gtk::Builder> popup_builder;
        std::shared_ptr<Glib::Dispatcher> popup_callback;
        bool cached = false;
        std::string policy_text;
    };
}