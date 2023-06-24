#include "../../include/explore-view/game-poster-preview.h"
#include "../../include/backend/game.h"
#include <thread>
#include <string>
#include <cpr/cpr.h>

namespace kurozora
{
    GamePosterPreview::GamePosterPreview(std::string game_id)
    {
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/game-poster-preview.ui"));
        container_box = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("container-box"));
        this->insert_child_at_start(*container_box);

        loading_overlay = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("loading-overlay"));
        preview_picture = std::shared_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("poster-preview"));
        game_title = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("game-title"));
        game_subtitle = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("game-subtitle"));
        control_button = std::shared_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));

        download_completed = std::make_shared<Glib::Dispatcher>();
        download_completed->connect([this]() {
            nlohmann::json& json_object = *(game->json_object);
            if (json_object["title"].is_string())
            {
                std::string title = json_object["title"];
                game_title->set_label(title);
                if (title.length() > 27)
                {
                    game_title->set_tooltip_text(title);
                }
            }
            if (json_object["tagline"].is_string())
            {
                std::string tagline = json_object["tagline"];
                game_subtitle->set_label(tagline);
                if (tagline.length() > 40) { game_subtitle->set_tooltip_text(tagline); }
            }
            else if (json_object["genres"].is_array() && json_object["genres"].size() > 0)
            {
                std::stringstream ss;
                for (auto& genre : json_object["genres"])
                {
                    ss << std::string(genre) << ", ";
                }
                std::string genres_subtitle = ss.str();
                genres_subtitle.pop_back(); // Remove last ` `
                genres_subtitle.pop_back(); // Remove last `,`
                game_subtitle->set_label(genres_subtitle);
                if (genres_subtitle.length() > 40) { game_subtitle->set_tooltip_text(genres_subtitle); }
            }
            else if (json_object["theme"].is_array() && json_object["theme"].size() > 0)
            {
                std::stringstream ss;
                for (auto& theme : json_object["theme"])
                {
                    ss << std::string(theme) << ", ";
                }
                std::string themes_subtitle = ss.str();
                themes_subtitle.pop_back(); // Remove last ` `
                themes_subtitle.pop_back(); // Remove last `,`
                game_subtitle->set_label(themes_subtitle);
                if (themes_subtitle.length() > 40) { game_subtitle->set_tooltip_text(themes_subtitle); }
            }
            else
            {
                game_subtitle->hide();
            }
            if (downloaded_texture.has_value())
            {
                preview_picture->set_paintable(downloaded_texture.value());
            }
            loading_overlay->hide();
        });

        this->game_id = game_id;
        std::thread download_game([this]() {
            game = std::make_shared<backend::Game>(backend::Game(this->game_id));
            nlohmann::json& json_object = *(game->json_object);
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
        download_game.detach();

    }
}