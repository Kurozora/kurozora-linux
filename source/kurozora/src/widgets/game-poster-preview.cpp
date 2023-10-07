#include "game-poster-preview.h"
#include "../../include/backend/game.h"
#include "../../include/utils/api/tagline.h"
#include <thread>
#include <string>
#include <cpr/cpr.h>

namespace kurozora
{
    GamePosterPreview::GamePosterPreview(const std::string& game_id)
    {
        addCssFile("/kurozora/ui/widgets/game-poster-preview/style.css");
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/game-poster-preview/definition.ui"));
        container_box = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("container-box"));
        this->insert_child_at_start(*container_box);

        loading_overlay = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("loading-overlay"));
        preview_picture = std::unique_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("poster-preview"));
        game_title = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("game-title"));
        game_subtitle = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("game-subtitle"));
        control_button = std::unique_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));

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
            std::optional<std::string> tagline = utils::api::compose_tagline(json_object);
            if (tagline.has_value())
            {
                game_subtitle->set_label(tagline.value());
                if (tagline.value().length() > 40)
                {
                    game_subtitle->set_tooltip_text(tagline.value());
                }
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
            game = std::make_unique<backend::Game>(backend::Game(this->game_id));
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