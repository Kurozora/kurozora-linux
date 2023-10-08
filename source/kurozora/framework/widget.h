#pragma once

#include <gtkmm.h>
#include <memory>
#include <vector>
#include <functional>

namespace kz::fw 
{
    //A widget with an initial "loading" process and a secondary "drawing" process.
    //The first function displays some placeholders/temporary stuff while retrieving data
    //from somehere (ex: API, Disk), once it's ready it calls the draw fucntion to display
    //the fetched data or the result of the loading process.
    class WidgetLoader : public Gtk::Box
    {
    public:
        void addCssFile(std::string gresource_path);
        void addCssClass(std::string css_code, std::string class_name);
    };
}
