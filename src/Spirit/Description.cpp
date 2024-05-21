#include "Spirit/Description.hpp"

std::string Description::format() const noexcept
{
    std::ostringstream oss;
    oss << "{" << std::endl;
    oss << "  \"name\": \"" << name << "\"," << std::endl;
    oss << "  \"description\": \"" << description << "\"," << std::endl;
    oss << "  \"petName\": \"" << petName << "\"" << std::endl;
    oss << "}" << std::endl;
    return oss.str();
}

nlohmann::json Description::toJson() const noexcept
{
    nlohmann::json j;
    j["name"] = name;
    j["description"] = description;
    j["petName"] = petName;
    return j;
}