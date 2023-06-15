#include "../../include/backend/anime.h"
#include <cpr/cpr.h>
#include <sstream>
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
            if (json_object["data"][0]["attributes"]["banner"]["url"].is_string())
            {
                banner_url = json_object["data"][0]["attributes"]["banner"]["url"];
            }
            if (json_object["data"][0]["attributes"]["title"].is_string())
            {
                title = json_object["data"][0]["attributes"]["title"];
            }
            if (json_object["data"][0]["attributes"]["tagline"].is_string())
            {
                tagline = json_object["data"][0]["attributes"]["tagline"];
            }
            if (json_object["data"][0]["attributes"]["genres"].is_array())
            {
                std::vector<std::string> genres_strings;
                for (auto& data : json_object["data"][0]["attributes"]["genres"])
                {
                    genres_strings.push_back(data);
                }
                genres = genres_strings;
            }
            if (json_object["data"][0]["attributes"]["themes"].is_array())
            {
                std::vector<std::string> themes_strings;
                for (auto& data : json_object["data"][0]["attributes"]["themes"])
                {
                    themes_strings.push_back(data);
                }
                themes = themes_strings;
            }
            if (json_object["data"][0]["attributes"]["stats"]["ratingAverage"].is_number_float())
            {
                rating_average = json_object["data"][0]["attributes"]["stats"]["ratingAverage"];
            }
        }
        catch (std::exception& e)
        {
            std::cerr << "ANIME OBJECT INIT ERROR:" << e.what() << std::endl;
            //throw e;
        }
    }
}