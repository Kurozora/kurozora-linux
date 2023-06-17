#include "../../include/explore-view/explore-view.h"
#include <thread>
#include <nlohmann/json.hpp>

namespace kurozora
{
    ExploreView::ExploreView(Gtk::Window* parent_window)
    {
        this->parent_window = parent_window;

        this->builder = Gtk::Builder::create_from_resource("/kurozora/ui/widgets/explore-view/explore-view.ui");
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

        // Initialize Widgets
        featured_container = std::shared_ptr<Gtk::Box>(this->builder->get_widget<Gtk::Box>("explore-featured"));
        this_season_container = std::shared_ptr<Gtk::Box>(builder->get_widget<Gtk::Box>("explore-season"));
        this_season_header = std::shared_ptr<Gtk::Label>(builder->get_widget<Gtk::Label>("this-season"));
        featured_callback = std::make_shared<Glib::Dispatcher>();
        featured_callback->connect([this]() {
            // Initialize Featured
            for (std::shared_ptr<ShowPreview> show_preview : featured_shows_previews)
            {
                featured_container->append(*show_preview);
            }
            this_season_header->set_text(this_season_string);
            for (std::shared_ptr<EntryPosterPreview> show_preview : this_season_previews)
            {
                this_season_container->append(*show_preview);
            }
        });

        featured_shows_previews.reserve(10);
        std::thread download_explore([this]() {
            explore = std::make_shared<backend::Explore>();
            nlohmann::json& json_object = *(explore->json_object);
            for (auto& category : json_object["data"])
            {
                if (category["attributes"]["type"] == "most-popular-shows")
                {
                    // Featured
                    for (auto& data : category["relationships"]["shows"]["data"])
                    {
                        //featured_anime_ids.push_back(data["id"]);
                        featured_shows_previews.push_back(std::make_shared<ShowPreview>(data["id"]));
                    }
                }
                if (category["attributes"]["type"] == "anime-season")
                {
                    this_season_string = std::string(category["attributes"]["title"]);
                    // This Season
                    for (auto& data : category["relationships"]["shows"]["data"])
                    {
                        //this_season_anime_ids.push_back(data["id"]);
                        this_season_previews.push_back(std::make_shared<EntryPosterPreview>(data["id"]));
                    }
                }
            }
            featured_callback->emit();
        });
        download_explore.detach();

        //Initialize the Kurozora & Privacy label
        this->privacy_label = std::make_shared<PrivacyLabel>(parent_window, this->builder, "explore-kurozora-privacy-label");

        this->insert_child_at_start(*this->explore_main_box);
        this->show();
    }

    void ExploreView::QuickLinkOpen(const std::string&& url)
    {
        // TODO: Add Windows compatibility
        system(std::string("open " + url).c_str());
    }
}