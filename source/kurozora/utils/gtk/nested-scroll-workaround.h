#pragma once

#include <gtkmm.h>
#include <memory>

namespace kurozora::utils::gtk
{
    // Horrifying workaround method to fix broken scrolling on nested `GtkScrolledWindow`
    // It takes a builder and applies the workaround to every `GtkScrolledWindow` called
    // `scrolled-window-workaround-*` where * is a number starting from 0
    void fix_nested_scroll(Gtk::Builder* builder);
}