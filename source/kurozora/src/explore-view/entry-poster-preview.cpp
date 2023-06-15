#include "../../include/explore-view/entry-poster-preview.h"
#include "../../include/backend/anime.h"
#include <thread>
#include <string>

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

        download_completed = std::shared_ptr<Glib::Dispatcher>(new Glib::Dispatcher());
        download_completed->connect([this]() {
            if (anime->title.has_value())
            {
                anime_title->set_label(anime->title.value());
                if (anime->title.value().length() > 27)
                {
                    anime_title->set_tooltip_text(anime->title.value());
                }
            }
            if (anime->tagline.has_value())
            {
                anime_subtitle->set_label(anime->tagline.value());
                if (anime->tagline.value().length() > 40) { anime_subtitle->set_tooltip_text(anime->tagline.value()); }
            }
            else if (anime->genres.has_value())
            {
                std::stringstream ss;
                for (auto& genre : anime->genres.value())
                {
                    ss << genre << ", ";
                }
                std::string genres_subtitle = ss.str();
                genres_subtitle.pop_back(); // Remove last ` `
                genres_subtitle.pop_back(); // Remove last `,`
                anime_subtitle->set_label(genres_subtitle);
                if (genres_subtitle.length() > 40) { anime_subtitle->set_tooltip_text(genres_subtitle); }
            }
            else if (anime->themes.has_value())
            {
                std::stringstream ss;
                for (auto& genre : anime->themes.value())
                {
                    ss << genre << ", ";
                }
                std::string themes_subtitle = ss.str();
                themes_subtitle.pop_back(); // Remove last ` `
                themes_subtitle.pop_back(); // Remove last `,`
                anime_subtitle->set_label(themes_subtitle);
                if (themes_subtitle.length() > 40) { anime_subtitle->set_tooltip_text(themes_subtitle); }
            }
            else
            {
                anime_subtitle->hide();
            }
            if (anime->rating_average.has_value())
            {
                std::string formatted_rating = std::to_string(anime->rating_average.value()).substr(0, 3);
                std::replace(formatted_rating.begin(), formatted_rating.end(), ',', '.');
                rating_label->set_label(formatted_rating);
                for (auto it = rating_stars.begin(); it != rating_stars.end();  ++it)
                {
                    if (anime->rating_average.value() - (it - rating_stars.begin()) > 0.0 &&
                        anime->rating_average.value() - (it - rating_stars.begin()) < 1.0)
                    {
                        (*it)->set_from_icon_name("rating_star_half");
                    }
                    else if (it - rating_stars.begin() < anime->rating_average.value())
                    {
                        (*it)->set_from_icon_name("rating_star_full");
                    }
                }
            }
        });

        this->anime_id = anime_id;
        std::thread download_anime([this]() {
            anime = std::make_shared<backend::Anime>(backend::Anime(this->anime_id));
            download_completed->emit();
        });
        download_anime.detach();

    }
}