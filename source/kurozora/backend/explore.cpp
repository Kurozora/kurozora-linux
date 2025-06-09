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
                cpr::Url("https://api.kurozora.app/v1/explore"),
                cpr::Header({{"User-Agent", "Kurozora/1.12.3 (app.kurozora.linux; build:1234; Linux 6.0.0) libcurl/1.1.1"}}),
                cpr::Header({{"X-Api-Key", "9t7WozArnqL30HLj3Y5aLfaB1LFFmdFJsCDOSkN6"}})
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