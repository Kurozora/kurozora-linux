#pragma once

#include <vector>

namespace kurozora::backend
{
    class Explore
    {
    public:
        Explore();
    public:
        std::vector<int> featured_anime_ids;
        std::vector<int> this_season_anime_ids;
    };
}