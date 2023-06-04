#pragma once

#include <gtkmm.h>
#include <memory>

namespace kurozora
{
    class ShowPreview :  public Gtk::Box
    {
    public:
        ShowPreview();
    private:
        std::shared_ptr<Gtk::Builder> builder;
        std::shared_ptr<Gtk::Box> box;
    };
}