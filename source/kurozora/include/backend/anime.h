#pragma once

#include <string>

namespace kurozora::backend
{
    class Anime
    {
    public:
        Anime(int anime_id);
    // This should not be public and writable, it's temporary
    public:
        std::string banner_url;
        std::string title;
        std::string tagline;
    };
}