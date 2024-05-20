#include "skill.hpp"

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
        oss << "      \"description\": \"" << effects[i].description << "\"," << std::endl;
        oss << "      \"target\": {" << std::endl;
        oss << "        \"goal\": " << GET_GOAL_STRING(effects[i].target.goal) << "," << std::endl;
        oss << "        \"type\": " << GET_TYPE_STRING(effects[i].target.type) << std::endl;
        oss << "      }," << std::endl;
        oss << "      \"source\": {" << std::endl;
        oss << "        \"goal\": " << GET_GOAL_STRING(effects[i].source.goal) << "," << std::endl;
        oss << "        \"type\": " << GET_TYPE_STRING(effects[i].source.type) << "," << std::endl;
        oss << "        \"value\": " << effects[i].source.value << std::endl;
        oss << "      }," << std::endl;
        oss << "      \"activationTime\": " << effects[i].activationTime << "," << std::endl;
        oss << "      \"duration\": " << effects[i].duration << std::endl;
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

std::string SkillManager::format() const noexcept
{
    std::ostringstream oss;
    oss << "{" << std::endl;
    oss << "  \"basicSkill\": " << basicSkill->format() << "," << std::endl;
    oss << "  \"specialSkill\": " << specialSkill->format() << "," << std::endl;
    oss << "  \"ultimateSkill\": " << ultimateSkill->format() << std::endl;
    oss << "}" << std::endl;
    return oss.str();
}