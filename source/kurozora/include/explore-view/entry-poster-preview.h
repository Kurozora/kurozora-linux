#pragma once

#include <gtkmm.h>
#include <memory>
#include <vector>

namespace kurozora
{
    class EntryPosterPreview : public Gtk::Box
    {
    public:
        EntryPosterPreview(int anime_id);
    private:
        int anime_id;
        float anime_rating;
        std::shared_ptr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::Box> container_box;
        std::shared_ptr<Gtk::Label> anime_title;
        std::shared_ptr<Gtk::Label> anime_subtitle;
        std::shared_ptr<Gtk::Label> rating_label;
        std::vector<std::shared_ptr<Gtk::Image>> rating_stars;
        std::shared_ptr<Gtk::Button> control_button;
    };
}