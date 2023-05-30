#pragma once

#include <gtkmm.h>

namespace kurozora
{
    class PrivacyLabel // This should be moved to it's own header file
    {
    public:
        PrivacyLabel(std::shared_ptr<Gtk::Builder> builder, const std::string&& label_id);
    public:
        std::shared_ptr<Gtk::Label> label;
        std::shared_ptr<Gtk::GestureClick> gesture_click;
        std::shared_ptr<Glib::Dispatcher> success_dispatcher;
        std::shared_ptr<Glib::Dispatcher> error_dispatcher;
    };

    class ExploreView : public Gtk::Box
    {
    public:
        ExploreView();
        void QuickLinkOpen(const std::string&& url);
    public:
        std::shared_ptr<Gtk::Box> explore_main_box;
        std::shared_ptr<Gtk::Builder> builder;

        // Quick Links Privacy Label
        std::shared_ptr<PrivacyLabel> privacy_label;
    };
}