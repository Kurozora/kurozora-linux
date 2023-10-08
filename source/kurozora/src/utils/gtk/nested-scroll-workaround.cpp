#include <gtkmm.h>
#include <memory>
#include <sstream>
#include "nested-scroll-workaround.h"

namespace kurozora::utils::gtk
{
    void fix_nested_scroll(Gtk::Builder* builder)
    {
        // Collect widgets for workaround
        std::vector<Gtk::ScrolledWindow*> scrolled_windows = std::vector<Gtk::ScrolledWindow*>();
        bool searching = true;
        int index = 0;
        while (searching)
        {
            std::stringstream widget_name;
            widget_name << "scrolled-window-workaround-";
            widget_name << index;
            if (builder->get_widget<Gtk::ScrolledWindow>(widget_name.str()) != nullptr)
            {
                scrolled_windows.push_back(builder->get_widget<Gtk::ScrolledWindow>(widget_name.str()));
                index++;
            }
            else
            {
                // An exception it thrown anyway is not found, but it's just a warning
                searching = false;
            }
        }
        // Found and collected all widgets, apply workaround
        for (Gtk::ScrolledWindow* scrolled_window : scrolled_windows)
        {
            int childrens_count = scrolled_window->observe_controllers()->get_n_items();
            for (int i = 0; i < childrens_count; ++i)
            {
                if (GTK_IS_EVENT_CONTROLLER_SCROLL(scrolled_window->observe_controllers()->get_object(i)->gobj()))
                {
                    GtkEventControllerScroll* event_controller_scroll = (GtkEventControllerScroll*)scrolled_window->observe_controllers()->get_object(i)->gobj();
                    gtk_event_controller_scroll_set_flags(event_controller_scroll, GtkEventControllerScrollFlags::GTK_EVENT_CONTROLLER_SCROLL_HORIZONTAL);
                }
            }
        }
    }
}