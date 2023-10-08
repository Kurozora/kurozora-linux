#pragma once

#include <nlohmann/json.hpp>
#include <memory>
#include <optional>
#include <vector>
#include <string>

namespace kurozora::backend
{
    class Game
    {
    public:
        Game(const std::string& game_id);
    // This should not be public and writable, it's temporary
    public:
        std::shared_ptr<nlohmann::json> json_object;
    };
}