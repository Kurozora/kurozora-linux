#pragma once

#include <gtkmm.h>
#include "privacy_label.h"

namespace kurozora
{
    class ExploreView : public Gtk::Box
    {
    public:
        ExploreView(std::shared_ptr<Gtk::Window> parent_window);
        void QuickLinkOpen(const std::string&& url);
    public:
        std::shared_ptr<Gtk::Window> parent_window;

        std::shared_ptr<Gtk::Box> explore_main_box;
        std::shared_ptr<Gtk::Builder> builder;

        // Quick Links Privacy Label
        std::shared_ptr<PrivacyLabel> privacy_label;
    };
}