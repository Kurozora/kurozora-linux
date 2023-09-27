#include "../../include/backend/genre.h"
#include <cpr/cpr.h>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace kurozora::backend
{
    Genre::Genre(const std::string genre_id)
    {
        try
        {
            // Retrieve & Parse json
            cpr::Response response = cpr::Get(
                cpr::Url(std::string("https://api.kurozora.app/v1/genres/" + genre_id)),
                cpr::Header({ { "Accept", "application/json" } })
            );
            if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve genres"); }
            json_object = std::make_shared<nlohmann::json>(nlohmann::json::parse(response.text)["data"]);
        }
        catch (std::exception& e)
        {
            std::cerr << "GAME OBJECT INIT ERROR:" << e.what() << std::endl;
            //throw e;
        }
    }
}