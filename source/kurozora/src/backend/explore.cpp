#include "../../include/backend/explore.h"
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>

namespace kurozora::backend
{
    Explore::Explore()
    {
        try
        {
            cpr::Response response = cpr::Get(
                cpr::Url("https://api.kurozora.app/v1/explore")
            );
            nlohmann::json json_object = nlohmann::json::parse(response.text);
            featured_anime_ids.reserve(10);
            // Iterated all the response sections
            for (auto& category : json_object["data"])
            {
                if (category["attributes"]["type"] == "most-popular-shows")
                {
                    // Featured
                    for (auto& data : category["relationships"]["shows"]["data"])
                    {
                        featured_anime_ids.push_back(data["id"]);
                    }
                }
                if (category["attributes"]["type"] == "anime-season")
                {
                    // This Season
                    for (auto& data : category["relationships"]["shows"]["data"])
                    {
                        this_season_anime_ids.push_back(data["id"]);
                    }
                }
            }
        }
        catch (std::exception& e)
        {
            std::cerr << "EXPLORE OBJECT INIT ERROR:" << e.what() << std::endl;
            throw e;
        }
    }
}