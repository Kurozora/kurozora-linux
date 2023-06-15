#include "../../include/explore-view/entry-poster-preview.h"
#include "../../include/backend/anime.h"
#include <iostream>

namespace kurozora
{
    EntryPosterPreview::EntryPosterPreview(int anime_id)
    {
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/entry-poster-preview.ui"));
        container_box = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("container-box"));
        this->insert_child_at_start(*container_box);

        anime_title = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-title"));
        anime_subtitle = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-subtitle"));
        rating_label = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("rating-label"));
        rating_stars.reserve(5);
        for (int i = 0; i < 5; ++i)
        {
            rating_stars.push_back(std::shared_ptr<Gtk::Image>(builder->get_widget<Gtk::Image>("rating-star-" + std::to_string(i+1))));
        }
        control_button = std::shared_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));

    }
}