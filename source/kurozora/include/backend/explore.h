#pragma once

#include <vector>

namespace kurozora::backend
{
    class Explore
    {
    public:
        Explore();
    public:
        // TODO: Throw away all of this and just forward the json::value object
        std::vector<int> featured_anime_ids;
        std::vector<int> this_season_anime_ids;
        std::string this_season_label = "";
    };
}