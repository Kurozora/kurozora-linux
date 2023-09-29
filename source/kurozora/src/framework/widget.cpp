#include "widget.h"

namespace kz::fw
{

    void WidgetLoader::addCssFile(std::string gresource_path) {}

    void WidgetLoader::addCssClass(std::string css_code, std::string class_name)
    {
        auto css_provider = Gtk::CssProvider::create();
        css_provider->load_from_data(css_code);
        auto display = this->get_style_context();
        display->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        display->add_class(class_name);
    }

}