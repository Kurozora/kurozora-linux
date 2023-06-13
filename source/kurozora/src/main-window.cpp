#include "../include/main-window.h"
#include "../include/explore-view/explore-view.h"

namespace kurozora
{
    MainWindow::MainWindow()
    {
        this->set_title("Kurozora");
        this->css_provider = Gtk::CssProvider::create();
        this->css_provider->load_from_resource("/kurozora/ui/style/overrides.css");
        this->builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/main-window.ui");

        this->main_box = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("main-window"));

        auto display = this->main_box->get_style_context()->get_display();
        this->get_style_context()->add_provider_for_display(display, this->css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        // Load custom icons
        GtkIconTheme* icon_theme_ref = gtk_icon_theme_get_for_display(display->gobj());
        gtk_icon_theme_add_resource_path(icon_theme_ref, "/kurozora/ui/icons/");

        this->set_child(*this->main_box);
        this->show();

        // Build the various sections of the app
        this->explore_view = new ExploreView(std::shared_ptr<Gtk::Window>(dynamic_cast<Gtk::Window*>(this)));
        this->builder->get_widget<Gtk::Box>("explore-container")->insert_child_at_start(*this->explore_view);
    }

    MainWindow::~MainWindow() {}
}