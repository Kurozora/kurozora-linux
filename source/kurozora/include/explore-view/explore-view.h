#pragma once

#include <gtkmm.h>
#include <cpr/cpr.h>
#include "../../src/widgets/privacy_label.h"
#include "../../src/widgets/show-preview.h"
#include "entry-poster-preview.h"
#include "game-poster-preview.h"
#include "../../src/widgets/large-show-poster.h"
#include "../../src/widgets/genre-horizontal-card.h"
#include "../backend/explore.h"

namespace kurozora
{
    class ExploreView : public Gtk::Box
    {
    public:
        ExploreView(Gtk::Window* parent_window);
        void QuickLinkOpen(const std::string&& url);
    public:
        Gtk::Window* parent_window;

        std::unique_ptr<Gtk::Box> explore_main_box;
        std::shared_ptr<Gtk::Builder> builder;

        // Scroll Workaround
        std::shared_ptr<Gtk::EventControllerScroll> eventControllerScroll;
        // Explore Object
        std::unique_ptr<backend::Explore> explore;
        // Featured Shows Previews
        std::unique_ptr<Glib::Dispatcher> featured_callback;
        std::unique_ptr<Gtk::Box> featured_container;
        std::vector<std::shared_ptr<ShowPreview>> featured_shows_previews = std::vector<std::shared_ptr<ShowPreview>>();
        // This Season Poster Previews
        std::string this_season_string;
        std::unique_ptr<Gtk::Label> this_season_header;
        std::unique_ptr<Gtk::Box> this_season_container;
        std::vector<std::shared_ptr<EntryPosterPreview>> this_season_previews = std::vector<std::shared_ptr<EntryPosterPreview>>();
        // New Games Additions
        std::unique_ptr<Gtk::Box> new_games_additions_container;
        std::vector<std::unique_ptr<GamePosterPreview>> new_game_additions_previews = std::vector<std::unique_ptr<GamePosterPreview>>();
        // Upcoming Shows
        std::unique_ptr<Gtk::Box> upcoming_shows_container;
        std::vector<std::unique_ptr<LargeShowPoster>> upcoming_shows = std::vector<std::unique_ptr<LargeShowPoster>>();
        // Top Genres
        std::unique_ptr<Gtk::Box> top_genres_container;
        std::vector<std::unique_ptr<GenreHorizontalCard>> top_genres_previews = std::vector<std::unique_ptr<GenreHorizontalCard>>();
        // What Are We Watching
        std::unique_ptr<Gtk::Box> what_are_we_watching_container;
        std::vector<std::unique_ptr<EntryPosterPreview>> what_are_we_watching_previews = std::vector<std::unique_ptr<EntryPosterPreview>>();
        // Quick Links Privacy Label
        std::unique_ptr<PrivacyLabel> privacy_label;
    };
}