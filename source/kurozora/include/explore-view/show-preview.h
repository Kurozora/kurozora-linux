#pragma once

#include <gtkmm.h>
#include <memory>
#include <string>
#include <optional>

namespace kurozora
{
    class ShowPreview :  public Gtk::Box
    {
    public:
        ShowPreview(int anime_id);
    private:
        int anime_id;
        std::shared_ptr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::Box> box;
        std::shared_ptr<Gtk::Box> loading_overlay;
        std::shared_ptr<Gtk::Label> anime_title;
        std::shared_ptr<Gtk::Label> anime_subtitle;
        std::shared_ptr<Gtk::Button> control_button;
        std::shared_ptr<Gtk::Picture> preview_picture;
        std::shared_ptr<Glib::Bytes> downloaded_buffer;
        std::optional<std::shared_ptr<Gdk::Texture>> downloaded_texture;
        std::shared_ptr<Glib::Dispatcher> download_completed;
        std::string title = "";
        std::optional<std::string> tagline = std::nullopt;
        std::string banner_url;
    };
}