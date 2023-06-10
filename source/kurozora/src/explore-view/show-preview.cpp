#include "../../include/explore-view/show-preview.h"
#include "../../include/backend/anime.h"
#include <cpr/cpr.h>
#include <exception>

namespace kurozora
{
    // TODO: This should take an anime ID and fetch the existing method starting from that, using an helper method
    ShowPreview::ShowPreview(int anime_id)
    {
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/show-preview.ui"));
        box = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("show-preview-entry"));
        this->insert_child_at_start(*box);

        loading_overlay = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("loading-overlay"));
        anime_title = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-title"));
        anime_subtitle = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-subtitle"));
        control_button = std::shared_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));
        preview_picture = std::shared_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("preview-picture"));


        download_completed = std::shared_ptr<Glib::Dispatcher>(new Glib::Dispatcher());
        download_completed->connect([this]() {
            // TODO: Not sure if this means that the placeholder stays in memory, and if so a single gresource copy or many
            if (downloaded_texture.has_value())
            {
                preview_picture->set_paintable(downloaded_texture.value());
            }
            anime_title->set_label(title);
            anime_subtitle->set_label(tagline);
            loading_overlay->hide();
        });

        this->anime_id = anime_id;
        std::thread download_image([this]() {
            backend::Anime anime = backend::Anime(this->anime_id);
        if (anime.title.has_value()) { title = anime.title.value(); } else { title = "No title!"; }
        if (anime.tagline.has_value()) { tagline = anime.tagline.value(); } else { tagline = "No tagline!"; }
            if (anime.banner_url.has_value())
            {
                // A picture URL has been specified, retrieve banner and replace placeholder immage
                cpr::Response response = cpr::Get(
                    cpr::Url(anime.banner_url.value()) // Temporary for testing
                );
                if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve banner image"); }
                downloaded_buffer = std::shared_ptr<Glib::Bytes>(Glib::Bytes::create(&response.text[0], response.text.length()));
                downloaded_texture = std::shared_ptr<Gdk::Texture>(Gdk::Texture::create_from_bytes(downloaded_buffer));
            }
            download_completed->emit();
        });
        download_image.detach();

        anime_title->set_label(title);
        anime_subtitle->set_label(tagline);
    }
}