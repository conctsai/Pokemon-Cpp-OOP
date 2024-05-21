#include "Spirit/Skill.hpp"

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
        oss << "        \"goal\": \"" << GET_GOAL_STRING(effects[i].target.goal) << "\"," << std::endl;
        oss << "        \"type\": \"" << GET_TYPE_STRING(effects[i].target.type) << "\"" << std::endl;
        oss << "      }," << std::endl;
        oss << "      \"source\": {" << std::endl;
        oss << "        \"goal\": \"" << GET_GOAL_STRING(effects[i].source.goal) << "\"," << std::endl;
        oss << "        \"type\": \"" << GET_TYPE_STRING(effects[i].source.type) << "\"," << std::endl;
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

nlohmann::json Skill::toJson() const noexcept
{
    nlohmann::json j;
    j["name"] = name;
    j["description"] = description;
    nlohmann::json effectsJson;
    for (size_t i = 0; i < effects.size(); i++)
    {
        nlohmann::json effectJson;
        effectJson["description"] = effects[i].description;
        nlohmann::json targetJson;
        targetJson["goal"] = GET_GOAL_STRING(effects[i].target.goal);
        targetJson["type"] = GET_TYPE_STRING(effects[i].target.type);
        effectJson["target"] = targetJson;
        nlohmann::json sourceJson;
        sourceJson["goal"] = GET_GOAL_STRING(effects[i].source.goal);
        sourceJson["type"] = GET_TYPE_STRING(effects[i].source.type);
        sourceJson["value"] = effects[i].source.value;
        effectJson["source"] = sourceJson;
        effectJson["activationTime"] = effects[i].activationTime;
        effectJson["duration"] = effects[i].duration;
        effectsJson.push_back(effectJson);
    }
    j["effects"] = effectsJson;
    return j;
}

nlohmann::json SkillManager::toJson() const noexcept
{
    nlohmann::json j;
    j["basicSkill"] = basicSkill->toJson();
    j["specialSkill"] = specialSkill->toJson();
    j["ultimateSkill"] = ultimateSkill->toJson();
    return j;
}