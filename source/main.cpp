#include "kurozora/include/main-window.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Starting Kurozora" << std::endl;
    auto app = Gtk::Application::create("app.Kurozora.Kurozora");
    return app->make_window_and_run<kurozora::MainWindow>(argc, argv);
}