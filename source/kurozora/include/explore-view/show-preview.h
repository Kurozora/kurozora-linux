#pragma once

#include <gtkmm.h>

namespace kurozora
{
    class ShowPreview :  public Gtk::Box
    {
    public:
        ShowPreview();
    private:
        std::shared_ptr<Gtk::Overlay> overlay;
        std::shared_ptr<Gtk::Box> bottom_bar_box;
        std::shared_ptr<Gtk::Box> labels_container_box;
        std::shared_ptr<Gtk::Label> title;
        std::shared_ptr<Gtk::Label> subtitle;
        std::shared_ptr<Gtk::Box> filler_box;
        std::shared_ptr<Gtk::Button> button;
        std::shared_ptr<Gtk::Picture> picture;
        std::shared_ptr<Gio::File> picture_content;
    };
}