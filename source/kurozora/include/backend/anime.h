#pragma once

#include <string>
#include <optional>
#include <vector>

namespace kurozora::backend
{
    class Anime
    {
    public:
        Anime(int anime_id);
    // This should not be public and writable, it's temporary
    public:
        std::optional<std::string> banner_url = std::nullopt;
        std::optional<std::string> title = std::nullopt;
        std::optional<std::string> tagline = std::nullopt;
        std::optional<std::vector<std::string>> genres = std::nullopt;
        std::optional<std::vector<std::string>> themes = std::nullopt;
    };
}