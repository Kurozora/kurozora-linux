#pragma once

#include <gtkmm.h>
#include <memory>
#include <optional>
#include <string>

namespace kurozora
{
    class ShowPreview :  public Gtk::Box
    {
    public:
        ShowPreview(const std::string&& title, const std::string&& subtitle, const std::optional<std::string>& picture_url = std::nullopt);
    private:
        std::shared_ptr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::Box> box;
        std::shared_ptr<Gtk::Label> anime_title;
        std::shared_ptr<Gtk::Label> anime_subtitle;
        std::shared_ptr<Gtk::Button> control_button;
        std::shared_ptr<Gtk::Picture> preview_picture;
        std::shared_ptr<Glib::Bytes> downloaded_buffer;
        std::shared_ptr<Gdk::Texture> downloaded_texture;
        std::shared_ptr<Glib::Dispatcher> download_completed;
    };
}