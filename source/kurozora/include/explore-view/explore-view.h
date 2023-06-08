#pragma once

#include <gtkmm.h>
#include <cpr/cpr.h>
#include "privacy_label.h"
#include "show-preview.h"

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

        // Sample Show Preview
        std::shared_ptr<Gtk::Box> featured_container;
        std::vector<std::shared_ptr<ShowPreview>> featured_shows_previews = std::vector<std::shared_ptr<ShowPreview>>();
        //std::shared_ptr<ShowPreview> sample_preview;
        // Quick Links Privacy Label
        std::shared_ptr<PrivacyLabel> privacy_label;
    };
}