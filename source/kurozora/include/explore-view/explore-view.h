#pragma once

#include <gtkmm.h>
#include <cpr/cpr.h>
#include "privacy_label.h"
#include "show-preview.h"
#include "../backend/explore.h"

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

        // Explore Object
        std::shared_ptr<backend::Explore> explore;
        // Featured Shows Previews
        std::shared_ptr<Gtk::Box> featured_container;
        std::vector<std::shared_ptr<ShowPreview>> featured_shows_previews = std::vector<std::shared_ptr<ShowPreview>>();
        // Quick Links Privacy Label
        std::shared_ptr<PrivacyLabel> privacy_label;
    };
}