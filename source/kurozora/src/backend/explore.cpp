#include "../backend/explore.h"
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
            json_object = std::make_shared<nlohmann::json>(nlohmann::json::parse(response.text));
        }
        catch (std::exception& e)
        {
            std::cerr << "EXPLORE OBJECT INIT ERROR:" << e.what() << std::endl;
            throw e;
        }
    }
}