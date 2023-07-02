#include "../../include/explore-view/large-show-poster.h"
#include "../../include/backend/anime.h"
#include "../../include/utils/api/tagline.h"
#include "../../include/utils/time/parse_time.h"
#include <cpr/cpr.h>
#include <exception>
#include <sstream>

namespace kurozora
{
    // TODO: This should take an anime ID and fetch the existing method starting from that, using an helper method
    LargeShowPoster::LargeShowPoster(int anime_id)
    {
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/large-show-poster.ui"));
        box = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("show-preview-entry"));
        this->insert_child_at_start(*box);

        loading_overlay = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("loading-overlay"));
        anime_title = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-title"));
        expected_date = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("expected-date"));
        control_button = std::unique_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));
        preview_picture = std::unique_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("preview-picture"));


        download_completed = std::make_shared<Glib::Dispatcher>();
        download_completed->connect([this]() {
            nlohmann::json& json_object = *(anime->json_object);
            if (json_object["title"].is_string())
            {
                std::string title = json_object["title"];
                anime_title->set_label(title);
                if (title.length() > 21)
                {
                    anime_title->set_tooltip_text(title);
                }
            }
            if (json_object["startedAt"].is_number_integer())
            {
                std::time_t unix_timestamp = (std::time_t)json_object["startedAt"].get<std::int64_t>();
                //std::time_t unix_timestamp = 1688256000;
                expected_date->set_label(utils::time::parse_time(&unix_timestamp));
            }
            else
            {
                expected_date->hide();
            }
            if (downloaded_texture.has_value())
            {
                preview_picture->set_paintable(downloaded_texture.value());
            }
            loading_overlay->hide();
        });

        this->anime_id = anime_id;
        std::thread download_image([this]() {
            anime = std::make_unique<backend::Anime>(backend::Anime(this->anime_id));
            nlohmann::json& json_object = *(anime->json_object);
            if (json_object["poster"]["url"].is_string())
            {
                cpr::Response response = cpr::Get(
                    cpr::Url(json_object["poster"]["url"])
                );
                if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve banner image"); }
                downloaded_buffer = std::shared_ptr<Glib::Bytes>(Glib::Bytes::create(&response.text[0], response.text.length()));
                downloaded_texture = std::shared_ptr<Gdk::Texture>(Gdk::Texture::create_from_bytes(downloaded_buffer));
            }
            download_completed->emit();
        });
        download_image.detach();

    }
}