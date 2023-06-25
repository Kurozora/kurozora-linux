#include "../../../include/utils/api/tagline.h"

namespace kurozora::utils::api
{
    std::optional<std::string> compose_tagline(const nlohmann::json& json_object)
    {
        if (json_object["tagline"].is_string())
        {
            if (std::string(json_object["tagline"]).size() > 0)
            {
                std::string tagline = json_object["tagline"];
                return std::move(tagline);
            }
        }
        else if (json_object["genres"].is_array())
        {
            if (json_object["genres"].size() > 0)
            {
                std::stringstream ss;
                for (auto& genre : json_object["genres"])
                {
                    ss << std::string(genre) << ", ";
                }
                std::string genres_subtitle = ss.str();
                genres_subtitle.pop_back(); // Remove last ` `
                genres_subtitle.pop_back(); // Remove last `,`
                return std::move(genres_subtitle);
            }
        }
        else if (json_object["themes"].is_array())
        {
            if (json_object["themes"].size() > 0)
            {
                std::stringstream ss;
                for (auto& theme : json_object["theme"])
                {
                    ss << std::string(theme) << ", ";
                }
                std::string themes_subtitle = ss.str();
                themes_subtitle.pop_back(); // Remove last ` `
                themes_subtitle.pop_back(); // Remove last `,`
                return std::move(themes_subtitle);
            }
        }

        //return std::move(ss.str());
        return std::nullopt;
    }
}