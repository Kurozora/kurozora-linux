#include "../include/main-window.h"

namespace kurozora
{
    MainWindow::MainWindow()
    {
        this->set_title("Kurozora");
        this->css_provider = Gtk::CssProvider::create();
        this->css_provider->load_from_path("../ui/style/overrides.css");
        this->builder = Gtk::Builder::create_from_file("../ui/widgets/main-window.ui");

        this->main_box = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("main-window"));

        auto display = this->main_box->get_style_context()->get_display();
        this->get_style_context()->add_provider_for_display(display, this->css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        this->set_child(*this->main_box);
        this->show();
    }

    MainWindow::~MainWindow() {}
}