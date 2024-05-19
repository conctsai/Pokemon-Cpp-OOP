#include "skill.h"

std::string Skill::format() const noexcept
{
    std::ostringstream oss;
    oss << "{" << std::endl;
    oss << "  \"name\": \"" << name << "\"," << std::endl;
    oss << "  \"description\": \"" << description << "\"," << std::endl;
    oss << "  \"effects\": [" << std::endl;
    for (size_t i = 0; i < effects.size(); i++)
    {
        oss << "    {" << std::endl;
        oss << "      \"type\": " << GET_TYPE_STRING(effects[i].type) << "," << std::endl;
        oss << "      \"value\": " << effects[i].value << "," << std::endl;
        oss << "      \"goal\": " << GET_GOAL_STRING(effects[i].goal) << "," << std::endl;
        oss << "      \"activationTime\": " << effects[i].activationTime << std::endl;
        oss << "    }";
        if (i != effects.size() - 1)
        {
            oss << ",";
        }
        oss << std::endl;
    }
    oss << "  ]" << std::endl;
    oss << "}" << std::endl;
    return oss.str();
}