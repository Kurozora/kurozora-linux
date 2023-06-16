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
        std::shared_ptr<backend::Anime> anime;
        std::shared_ptr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::Box> container_box;
        std::shared_ptr<Gtk::Label> anime_title;
        std::shared_ptr<Gtk::Label> anime_subtitle;
        std::shared_ptr<Gtk::Label> rating_label;
        std::vector<std::shared_ptr<Gtk::Image>> rating_stars;
        std::shared_ptr<Gtk::Button> control_button;
        std::shared_ptr<Glib::Dispatcher> download_completed;
        std::shared_ptr<Glib::Bytes> downloaded_buffer;
        std::optional<std::shared_ptr<Gdk::Texture>> downloaded_texture;
        std::shared_ptr<Gtk::Picture> preview_picture;
        std::shared_ptr<Gtk::Box> loading_overlay;
    };
}