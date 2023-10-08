#pragma once

#include "../framework/widget.h"

#include <gtkmm.h>
#include <memory>
#include <string>
#include <optional>
#include <vector>

namespace kurozora
{
    class ShowPreview : public kz::fw::WidgetHelper
    {
    public:
        ShowPreview(int anime_id);
    private:
        int anime_id;
        std::shared_ptr<Gtk::Builder> builder;
        std::unique_ptr<Gtk::Box> box;
        std::unique_ptr<Gtk::Box> loading_overlay;
        std::unique_ptr<Gtk::Label> anime_title;
        std::unique_ptr<Gtk::Label> anime_subtitle;
        std::unique_ptr<Gtk::Button> control_button;
        std::unique_ptr<Gtk::Picture> preview_picture;
        std::shared_ptr<Glib::Bytes> downloaded_buffer;
        std::optional<std::shared_ptr<Gdk::Texture>> downloaded_texture;
        std::shared_ptr<Glib::Dispatcher> download_completed;
        std::string title = "";
        std::optional<std::string> tagline = std::nullopt;
        std::optional<std::vector<std::string>> genres = std::nullopt;
        std::optional<std::vector<std::string>> themes = std::nullopt;
        std::string banner_url;
    };
}