#include "../../include/explore-view/show-preview.h"
#include <cpr/cpr.h>
#include <exception>

namespace kurozora
{
    // TODO: This should take an anime ID and fetch the existing method starting from that, using an helper method
    ShowPreview::ShowPreview(const std::string&& title, const std::string&& subtitle, const std::optional<std::string>& picture_url)
    {
        builder = std::shared_ptr<Gtk::Builder>(Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/show-preview.ui"));
        box = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("show-preview-entry"));
        this->insert_child_at_start(*box);

        anime_title = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-title"));
        anime_subtitle = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("anime-subtitle"));
        control_button = std::shared_ptr<Gtk::Button>(builder->get_widget<Gtk::Button>("control-button"));
        preview_picture = std::shared_ptr<Gtk::Picture>(builder->get_widget<Gtk::Picture>("preview-picture"));

        if (picture_url.has_value())
        {
            try
            {
                // A picture URL has been specified, retrieve banner and replace placeholder immage
                cpr::Response response = cpr::Get(
                    cpr::Url(picture_url.value())
                );
                if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve banner image"); }
                downloaded_buffer = std::shared_ptr<Glib::Bytes>(Glib::Bytes::create(&response.text[0], response.text.length()));
                downloaded_texture = std::shared_ptr<Gdk::Texture>(Gdk::Texture::create_from_bytes(downloaded_buffer));
                // TODO: Not sure if this means that the placeholder stays in memory, and if so a single gresource copy or many
                preview_picture->set_paintable(downloaded_texture);
            }
            catch (std::exception& e)
            {
                // It's fine, we can just display the already set placeholder
                // TODO: Might want to display a popup or a label, or maybe a different placeholder for an existing
                // image that we failed to retrieve
            }
        }

        anime_title->set_label(title);
        anime_subtitle->set_label(subtitle);
    }
}