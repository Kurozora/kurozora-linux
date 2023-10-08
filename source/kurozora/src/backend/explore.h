#pragma once

#include <nlohmann/json.hpp>

namespace kurozora::backend
{
    class Explore
    {
    public:
        Explore();
    public:
        std::shared_ptr<nlohmann::json> json_object;
    };
}