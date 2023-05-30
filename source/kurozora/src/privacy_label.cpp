#include "../include/explore-view.h" // TODO: Move this widget to it's own .h file
#include <thread>
#include <iostream> // Temporary for testing

namespace kurozora
{
    // TODO: Complete this!
    // This workflows allow you to not lock the main GTK thread while running long tasks
    // 1 - Button receives input, starts a widget like a spinner and then starts and detatches a thread for a long task
    // 2 - Thread does it's lengthy task like waiting for an HTTP response
    // 3 - Thread notifies via the dispatcher object that the work is finished
    //
    // The dispatcher object is created in advanced, linked to a function and then passed to the working thread.
    PrivacyLabel::PrivacyLabel(std::shared_ptr<Gtk::Builder> builder, const std::string&& label_id)
    {
        label = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>(label_id));

        // Initialize popup_window
        popup_window = std::shared_ptr<Gtk::Window>(new Gtk::Window);
        popup_window->set_hide_on_close();
        //popup_window->signal_close_request().connect([this]() -> bool {
        //    this->popup_window->hide();
        //    return true; 
        //}, false);

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