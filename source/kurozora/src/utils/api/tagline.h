#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <optional>
#include <sstream>

namespace kurozora::utils::api
{
    std::optional<std::string> compose_tagline(const nlohmann::json& value);
}