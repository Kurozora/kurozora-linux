#pragma once

#include <gtkmm.h>
#include <memory>
#include <vector>
#include "../../include/backend/anime.h"

namespace kurozora
{
    class EntryPosterPreview : public Gtk::Box
    {
    public:
        EntryPosterPreview(int anime_id);
    private:
        int anime_id;
        std::unique_ptr<backend::Anime> anime;
        std::shared_ptr<Gtk::Builder> builder;
        std::unique_ptr<Gtk::Box> container_box;
        std::unique_ptr<Gtk::Label> anime_title;
        std::unique_ptr<Gtk::Label> anime_subtitle;
        std::unique_ptr<Gtk::Label> rating_label;
        std::vector<std::unique_ptr<Gtk::Image>> rating_stars;
        std::unique_ptr<Gtk::Button> control_button;
        std::unique_ptr<Glib::Dispatcher> download_completed;
        std::shared_ptr<Glib::Bytes> downloaded_buffer;
        std::optional<std::shared_ptr<Gdk::Texture>> downloaded_texture;
        std::unique_ptr<Gtk::Picture> preview_picture;
        std::unique_ptr<Gtk::Box> loading_overlay;
    };
}