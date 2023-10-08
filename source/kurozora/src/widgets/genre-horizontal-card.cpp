#include "genre-horizontal-card.h"
#include "../backend/genre.h"
#include "../../include/utils/api/tagline.h"
#include <thread>
#include <string>
#include <cpr/cpr.h>
#include <regex>
#include <iostream>

namespace kurozora
{
    GenreHorizontalCard::GenreHorizontalCard(const std::string& genre_id)
    {
        addCssFile("/kurozora/ui/widgets/genre-horizontal-banner/style.css");
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/genre-horizontal-banner/definition.ui"));
        container_box = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("container-box"));
        this->insert_child_at_start(*container_box);

        loading_overlay = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("loading-overlay"));
        preview_picture = std::unique_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("preview-picture"));
        genre_title = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("genre-name"));
        gradient_background = std::unique_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("gradient-background"));

        download_completed = std::make_shared<Glib::Dispatcher>();
        download_completed->connect([this]() {
            nlohmann::json& json_object = *(genre->json_object);
            if (json_object[0]["attributes"]["backgroundColor1"].is_string() &&
                json_object[0]["attributes"]["backgroundColor2"].is_string())
            {
                // The 80 atfer the placeholder will result in transparency in HEX format after substitution
                std::string gradient_css_template = R"(

                    .genre-horizontal-card-runtime-background-gradient {
                        background-image: linear-gradient(BG_COLOR_180, BG_COLOR_280);
                        border-radius: 10px;
                        padding-bottom: 1.2em;
                    }

                )";

                std::string bg_color_1 = json_object[0]["attributes"]["backgroundColor1"];
                std::string bg_color_2 = json_object[0]["attributes"]["backgroundColor2"];
                gradient_css_template = std::regex_replace(gradient_css_template, std::regex("BG_COLOR_1"), bg_color_1);
                gradient_css_template = std::regex_replace(gradient_css_template, std::regex("BG_COLOR_2"), bg_color_2);

                addCssClass(gradient_css_template, "genre-horizontal-card-runtime-background-gradient");
            }
            if (json_object[0]["attributes"]["name"].is_string())
            {
                std::string genre_title_string = json_object[0]["attributes"]["name"];
                genre_title->set_label(genre_title_string);
            }
            if (downloaded_texture.has_value())
            {
                preview_picture->set_paintable(downloaded_texture.value());
            }
            loading_overlay->hide();
            });

        this->genre_id = genre_id;
        std::thread download_genre([this]() {
            genre = std::make_unique<backend::Genre>(backend::Genre(this->genre_id));
            nlohmann::json& json_object = *(genre->json_object);
            if (json_object[0]["attributes"]["symbol"]["url"].is_string())
            {
                cpr::Response response = cpr::Get(
                    cpr::Url(json_object[0]["attributes"]["symbol"]["url"])
                );
                if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve poster picture"); }
                downloaded_buffer = std::shared_ptr<Glib::Bytes>(Glib::Bytes::create(&response.text[0], response.text.length()));
                downloaded_texture = std::shared_ptr<Gdk::Texture>(Gdk::Texture::create_from_bytes(downloaded_buffer));
            }
            download_completed->emit();
            });
        download_genre.detach();

    }
}