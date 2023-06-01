#include "../../include/explore-view/explore-view.h"
#include <thread>

namespace kurozora
{
    ExploreView::ExploreView(std::shared_ptr<Gtk::Window> parent_window)
    {
        this->parent_window = parent_window;

        this->builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view.ui");
        this->explore_main_box = std::shared_ptr<Gtk::Box>(this->builder->get_widget<Gtk::Box>("explore_main_box"));

        // Initialize the Quick Links buttons
        auto quick_link_1 = std::shared_ptr<Gtk::FlowBoxChild>(this->builder->get_widget<Gtk::FlowBoxChild>("explore-quick-link-1"));
        auto quick_link_1_gesture = Gtk::GestureClick::create();
        quick_link_1_gesture->signal_released().connect([this](const int&, const double&, const double&) {QuickLinkOpen("https://kurozora.app/kb/iap"); });
        quick_link_1->add_controller(quick_link_1_gesture);

        auto quick_link_2 = std::shared_ptr<Gtk::FlowBoxChild>(this->builder->get_widget<Gtk::FlowBoxChild>("explore-quick-link-2"));
        auto quick_link_2_gesture = Gtk::GestureClick::create();
        quick_link_2_gesture->signal_released().connect([this](const int&, const double&, const double&) {QuickLinkOpen("https://kurozora.app/kb/personalisation"); });
        quick_link_2->add_controller(quick_link_2_gesture);

        auto quick_link_3 = std::shared_ptr<Gtk::FlowBoxChild>(this->builder->get_widget<Gtk::FlowBoxChild>("explore-quick-link-3"));
        auto quick_link_3_gesture = Gtk::GestureClick::create();
        quick_link_3_gesture->signal_released().connect([this](const int&, const double&, const double&) {QuickLinkOpen("https://kurozora.app/welcome"); });
        quick_link_3->add_controller(quick_link_3_gesture);

        // Initialize the Kurozora & Privacy label
        this->privacy_label = std::shared_ptr<PrivacyLabel>(new PrivacyLabel(parent_window, this->builder, "explore-kurozora-privacy-label"));

        this->insert_child_at_start(*this->explore_main_box);
        this->show();
    }

    void ExploreView::QuickLinkOpen(const std::string&& url)
    {
        // TODO: Add Windows compatibility
        system(std::string("open " + url).c_str());
    }
}