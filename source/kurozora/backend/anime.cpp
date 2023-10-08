#include "../backend/anime.h"
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
            json_object = std::make_shared<nlohmann::json>(nlohmann::json::parse(response.text)["data"][0]["attributes"]);
        }
        catch (std::exception& e)
        {
            std::cerr << "ANIME OBJECT INIT ERROR:" << e.what() << std::endl;
            //throw e;
        }
    }
}