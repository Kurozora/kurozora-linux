#include "entry-poster-preview.h"
#include "../../include/backend/anime.h"
#include "../../include/utils/api/tagline.h"
#include <thread>
#include <string>
#include <cpr/cpr.h>

namespace kurozora
{
    EntryPosterPreview::EntryPosterPreview(int anime_id)
    {
        addCssFile("/kurozora/ui/widgets/entry-poster-preview/style.css");
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/entry-poster-preview.ui"));
        container_box = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("container-box"));
        this->insert_child_at_start(*container_box);

        loading_overlay = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("loading-overlay"));
        preview_picture = std::unique_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("poster-preview"));
        anime_title = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-title"));
        anime_subtitle = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-subtitle"));
        rating_label = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("rating-label"));
        rating_stars.reserve(5);
        for (int i = 0; i < 5; ++i)
        {
            rating_stars.push_back(std::unique_ptr<Gtk::Image>(builder->get_widget<Gtk::Image>("rating-star-" + std::to_string(i+1))));
        }
        control_button = std::unique_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));

        download_completed = std::make_unique<Glib::Dispatcher>();
        download_completed->connect([this]() {
            nlohmann::json& json_object = *(anime->json_object);
            if (json_object["title"].is_string())
            {
                std::string title = json_object["title"];
                anime_title->set_label(title);
                if (title.length() > 27)
                {
                    anime_title->set_tooltip_text(title);
                }
            }
            std::optional<std::string> tagline = utils::api::compose_tagline(json_object);
            if (tagline.has_value())
            {
                anime_subtitle->set_label(tagline.value());
                if (tagline.value().length() > 40)
                {
                    anime_subtitle->set_tooltip_text(tagline.value());
                }
            }
            else
            {
                anime_subtitle->hide();
            }
            if (json_object["stats"]["ratingAverage"].is_number_float() && json_object["stats"]["ratingCount"].is_number_integer())
            {
                if (json_object["stats"]["ratingCount"].get<std::int64_t>() > 0)
                {
                    float rating_average = json_object["stats"]["ratingAverage"];
                    std::string formatted_rating = std::to_string(rating_average).substr(0, 3);
                    std::replace(formatted_rating.begin(), formatted_rating.end(), ',', '.');
                    rating_label->set_label(formatted_rating);
                    for (auto it = rating_stars.begin(); it != rating_stars.end(); ++it)
                    {
                        (*it)->set_visible(true);
                        if (rating_average - (it - rating_stars.begin()) > 0.0 &&
                            rating_average - (it - rating_stars.begin()) < 1.0)
                        {
                            (*it)->set_from_icon_name("rating_star_half");
                        }
                        else if (it - rating_stars.begin() < rating_average)
                        {
                            (*it)->set_from_icon_name("rating_star_full");
                        }
                    }
                }
            }
            if (downloaded_texture.has_value())
            {
                preview_picture->set_paintable(downloaded_texture.value());
            }
            loading_overlay->hide();
        });

        this->anime_id = anime_id;
        std::thread download_anime([this]() {
            anime = std::make_unique<backend::Anime>(backend::Anime(this->anime_id));
            nlohmann::json& json_object = *(anime->json_object);
            if (json_object["poster"]["url"].is_string())
            {
                cpr::Response response = cpr::Get(
                    cpr::Url(json_object["poster"]["url"])
                );
                if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve poster picture"); }
                downloaded_buffer = std::shared_ptr<Glib::Bytes>(Glib::Bytes::create(&response.text[0], response.text.length()));
                downloaded_texture = std::shared_ptr<Gdk::Texture>(Gdk::Texture::create_from_bytes(downloaded_buffer));
            }
            download_completed->emit();
        });
        download_anime.detach();

    }
}