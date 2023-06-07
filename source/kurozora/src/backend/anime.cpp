#include "../../include/backend/anime.h"
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>

namespace kurozora::backend
{
    Anime::Anime(int anime_id)
    {
        try
        {
            // Retrieve & Parse json
            cpr::Response response = cpr::Get(
                cpr::Url(std::string("https://api.kurozora.app/v1/anime/" + std::to_string(anime_id))),
                cpr::Header( {{ "Accept", "application/json" }} )
            );
            if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve banner image"); }
            nlohmann::json json_object = nlohmann::json::parse(response.text);

            // Json validation
            //  Temporary! Needs to check and stuff, just adding something I need now
            banner_url = json_object["data"][0]["attributes"]["banner"]["url"];
            title = json_object["data"][0]["attributes"]["title"];
            tagline = json_object["data"][0]["attributes"]["tagline"];
        }
        catch (std::exception& e)
        {
            std::cerr << "ANIME OBJECT INIT ERROR:" << e.what() << std::endl;
            throw e;
        }
    }
}