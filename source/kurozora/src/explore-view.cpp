#include "../include/explore-view.h"

namespace kurozora
{
    ExploreView::ExploreView()
    {
        this->builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view.ui");
        this->explore_main_box = std::shared_ptr<Gtk::Box>(this->builder->get_widget<Gtk::Box>("explore_main_box"));

        this->insert_child_at_start(*this->explore_main_box);
        this->show();
    }
}