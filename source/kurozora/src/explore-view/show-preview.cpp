#include "../../include/explore-view/show-preview.h"

namespace kurozora
{
    // WARNING: This is horrible
    /*
    I wanted to do something pretty using the UI file (resources/ui/widgets/explore-view/show-preview.ui)
    But unfortunately GTKmm4 does not support templates, nor a decent way to use XML files for reusable widgets.
    The "solution" will be somehow creating a utility that can parse XML files and create objects such as this one
    a good start could be from Gtk::Builder itself.
    */
    ShowPreview::ShowPreview()
    {
        // START Bottom Bar
        button = std::shared_ptr<Gtk::Button>(new Gtk::Button());
        button->set_sensitive(false); // Temporarily disabled since not implemented
        button->set_halign(Gtk::Align::END);
        button->set_valign(Gtk::Align::END);
        button->set_label("Add");

        filler_box = std::shared_ptr<Gtk::Box>(new Gtk::Box());
        filler_box->set_halign(Gtk::Align::FILL);
        filler_box->set_hexpand(true);

        // START Title and Subtitle
        title = std::shared_ptr<Gtk::Label>(new Gtk::Label());
        title->set_label("Oshi No Ko");
        title->set_halign(Gtk::Align::START);
        title->add_css_class("featured-show-overlay-box-label-title");

        subtitle = std::shared_ptr<Gtk::Label>(new Gtk::Label());
        subtitle->set_label("The bestest anime ever!");
        subtitle->set_halign(Gtk::Align::START);
        subtitle->add_css_class("featured-show-overlay-box-label-subtitle");

        labels_container_box = std::shared_ptr<Gtk::Box>(new Gtk::Box);
        labels_container_box->set_orientation(Gtk::Orientation::VERTICAL);
        labels_container_box->insert_child_at_start(*subtitle);
        labels_container_box->insert_child_at_start(*title);
        // END Title and Subtitle

        bottom_bar_box = std::shared_ptr<Gtk::Box>(new Gtk::Box());
        bottom_bar_box->add_css_class("featured-show-overlay-box");
        bottom_bar_box->set_valign(Gtk::Align::END);
        bottom_bar_box->set_halign(Gtk::Align::FILL);
        bottom_bar_box->set_hexpand(true);
        bottom_bar_box->set_orientation(Gtk::Orientation::HORIZONTAL);
        bottom_bar_box->insert_child_at_start(*button);
        bottom_bar_box->insert_child_at_start(*filler_box);
        bottom_bar_box->insert_child_at_start(*labels_container_box);
        // END Bottom Bar

        picture = std::shared_ptr<Gtk::Picture>(new Gtk::Picture());
        picture->add_css_class("featured-show-preview");
        picture->set_content_fit(Gtk::ContentFit::FILL);
        picture->set_filename("resource://kurozora/ui/placeholders/show_banner.jpg");
        // TODO: Set File

        overlay = std::shared_ptr<Gtk::Overlay>(new Gtk::Overlay());
        overlay->set_child(*picture);
        overlay->add_overlay(*bottom_bar_box);

        this->insert_child_at_start(*overlay);

        this->show();
    }
}