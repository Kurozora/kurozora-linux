#include "../include/main-window.h"

namespace kurozora
{
    MainWindow::MainWindow()
    {
        this->set_title("Kurozora");
        this->builder = Gtk::Builder::create_from_file("../ui/main-window.ui");
        this->window = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("main-window"));
        this->set_child(*this->window);
        this->show();
    }

    MainWindow::~MainWindow() {}
}