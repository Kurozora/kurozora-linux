#include "../include/explore-view.h" // TODO: Move this widget to it's own .h file
#include <thread>
#include <iostream> // Temporary for testing

namespace kurozora
{

    PrivacyLabel::PrivacyLabel(std::shared_ptr<Gtk::Window> parent, std::shared_ptr<Gtk::Builder> builder, const std::string&& label_id)
    {
        label = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>(label_id));

        std::shared_ptr<Gtk::Builder> popup_builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/privacy-label-popup.ui");
        popup_window = std::shared_ptr<Gtk::Window>(popup_builder->get_widget<Gtk::Window>("explore-privacy-label-popup-window"));
        popup_window->set_transient_for(*parent);
        popup_window->set_hide_on_close(true);

        //  Initialize callbacks
        success_dispatcher = std::shared_ptr<Glib::Dispatcher>(new Glib::Dispatcher);
        success_dispatcher->connect([this]() {
            // Success!
            std::cout << "Thread callback dispatcher success!" << std::endl;
            // Remove spinner and show text
        });
        error_dispatcher = std::shared_ptr<Glib::Dispatcher>(new Glib::Dispatcher);
        error_dispatcher->connect([this]() {
            // Error :(
            std::cout << "Thread callback dispatcher error!" << std::endl;
            
            // Show error message
        });

        // Create gesture & attach it to the label
        gesture_click = Gtk::GestureClick::create();
        gesture_click->signal_released().connect([this](const int&, const double&, const double&) {
            // Retrieve policy
            std::cout << "Clicked Button" << std::endl;
            this->popup_window->show();
            std::thread retrieve_privacy_notice([this]() {
                std::cout << "Thread running..." << std::endl;
                // CPR to fetch and parse response
                sleep(5);
                this->success_dispatcher->emit(); // Call the correct dispatcher
            });
            retrieve_privacy_notice.detach();
        });

        label->add_controller(gesture_click);
    }
}