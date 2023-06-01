#include "../include/explore-view.h" // TODO: Move this widget to it's own .h file
#include <thread>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream> // Temporary for testing

namespace kurozora
{

    PrivacyLabel::PrivacyLabel(std::shared_ptr<Gtk::Window> parent, std::shared_ptr<Gtk::Builder> builder, const std::string&& label_id)
    {
        label = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>(label_id));

        popup_builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/privacy-label-popup.ui");
        popup_text = std::shared_ptr<Gtk::TextView>(this->popup_builder->get_widget<Gtk::TextView>("explore-privacy-label-popup-text-view"));
        popup_window = std::shared_ptr<Gtk::Window>(popup_builder->get_widget<Gtk::Window>("explore-privacy-label-popup-window"));
        popup_window->set_transient_for(*parent);
        popup_window->set_hide_on_close(true);

        gesture_click = Gtk::GestureClick::create();
        gesture_click->signal_released().connect([this](const int&, const double&, const double&) {
            // Retrieve policy
            std::cout << "Clicked Button" << std::endl;
            this->popup_window->show();
            std::thread retrieve_privacy_notice([this]() {
                std::cout << "Thread running..." << std::endl;
                try
                {
                    cpr::Response response = cpr::Get(
                        cpr::Url("https://api.kurozora.app/v1/legal/privacy-policy")
                    );
                    if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve privacy policy"); }
                    nlohmann::json response_object = nlohmann::json::parse(response.text);
                    if (!response_object["data"]["attributes"]["text"].is_string()) { throw std::runtime_error("Error: malformed response"); }
                    this->popup_text->get_buffer()->set_text(std::string(response_object["data"]["attributes"]["text"]));;
                }
                catch (std::exception& e)
                {
                    // An error Occurred
                    this->popup_text->get_buffer()->set_text(std::string("An error occurred, please try again."));
                }
            });
            retrieve_privacy_notice.detach();
        });

        label->add_controller(gesture_click);
    }
}