#include "privacy_label.h"
#include <thread>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

namespace kurozora
{

    PrivacyLabel::PrivacyLabel(Gtk::Window* parent, std::shared_ptr<Gtk::Builder> builder, const std::string&& label_id)
    {
        label = std::unique_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>(label_id));

        addCssFile("/kurozora/ui/widgets/privacy-label/popup-style.css");
        popup_builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/privacy-label/popup-definition.ui");
        popup_text = std::unique_ptr<Gtk::TextView>(this->popup_builder->get_widget<Gtk::TextView>("explore-privacy-label-popup-text-view"));
        popup_window = std::unique_ptr<Gtk::Window>(popup_builder->get_widget<Gtk::Window>("explore-privacy-label-popup-window"));
        popup_window->set_transient_for(*parent);
        popup_window->set_hide_on_close(true);

        popup_callback = std::make_shared<Glib::Dispatcher>();
        popup_callback->connect([this]() {
            this->popup_text->get_buffer()->set_text(this->policy_text);
        });

        gesture_click = Gtk::GestureClick::create();
        gesture_click->signal_released().connect([this](const int&, const double&, const double&) {
            // Retrieve policy
            this->popup_window->show();
            std::thread retrieve_privacy_notice([this]() {
                try
                {
                    if (!cached)
                    {
                        cpr::Response response = cpr::Get(
                            cpr::Url("https://api.kurozora.app/v1/legal/privacy-policy")
                        );
                        if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve privacy policy"); }
                        nlohmann::json response_object = nlohmann::json::parse(response.text);
                        if (!response_object["data"]["attributes"]["text"].is_string()) { throw std::runtime_error("Error: malformed response"); }
                        this->policy_text = response_object["data"]["attributes"]["text"];
                        this->cached = true;
                        this->popup_callback->emit();
                    }
                }
                catch (std::exception& e)
                {
                    // An error Occurred
                    std::stringstream ss;
                    ss << "An error occurred, please try again. \n\n";
                    ss << e.what();
                    this->policy_text = std::string(ss.str());
                    this->popup_callback->emit();
                }
            });
            retrieve_privacy_notice.detach();
        });

        label->add_controller(gesture_click);
    }
}