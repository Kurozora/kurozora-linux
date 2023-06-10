#include "../../../include/utils/widgets/show-preview.h"

namespace kurozora::utils::show_preview
{
    std::string normalize_title(const std::string& input_string)
    {
        std::string output = input_string;
        if (output.length() > 27)
        {
            output = output.substr(0, 24).append("...");
        }
        return output;
    }

    std::string normalize_subtitle(const std::string& input_string)
    {
        std::string output = input_string;
        if (output.length() > 40)
        {
            output = output.substr(0, 37).append("...");
        }
        return output;
    }
}