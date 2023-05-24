#include "../include/main-window.h"

namespace kurozora
{
    MainWindow::MainWindow()
    {
        this->set_title("Kurozora");
        this->css_provider = Gtk::CssProvider::create();
        this->css_provider->load_from_path("../ui/style/main-window.css");
        this->builder = Gtk::Builder::create_from_file("../ui/widgets/main-window.ui");

        // This CSS file will only be applied to the main windget, for Kurozora global themes
        // it will make sense to retrieve the display object and apply the theme globally
        this->window = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("main-window"));
        this->window->get_style_context()->add_provider(this->css_provider, 1);

        this->set_child(*this->window);
        this->show();
    }

    MainWindow::~MainWindow() {}
}