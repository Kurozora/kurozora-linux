#pragma once

#include <gtkmm.h>
#include <memory>
#include <vector>
#include "../../include/backend/game.h"

namespace kurozora
{
    class GamePosterPreview : public Gtk::Box
    {
    public:
        GamePosterPreview(const std::string& game_id);
    private:
        std::string game_id;
        std::unique_ptr<backend::Game> game;
        std::shared_ptr<Gtk::Builder> builder;
        std::unique_ptr<Gtk::Box> container_box;
        std::unique_ptr<Gtk::Label> game_title;
        std::unique_ptr<Gtk::Label> game_subtitle;
        std::unique_ptr<Gtk::Button> control_button;
        std::shared_ptr<Glib::Dispatcher> download_completed;
        std::shared_ptr<Glib::Bytes> downloaded_buffer;
        std::optional<std::shared_ptr<Gdk::Texture>> downloaded_texture;
        std::unique_ptr<Gtk::Picture> preview_picture;
        std::unique_ptr<Gtk::Box> loading_overlay;
    };
}