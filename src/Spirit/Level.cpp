#include "Spirit/Level.hpp"

std::string Level::format() const noexcept
{
    std::ostringstream oss;
    oss << "{" << std::endl;
    oss << "  \"level\": " << level << "," << std::endl;
    oss << "  \"exp\": " << exp << "," << std::endl;
    oss << "  \"expToNextLevel\": " << expToNextLevel << "," << std::endl;
    oss << "  \"progress\": \"" << progress << "%\"" << std::endl;
    oss << "}" << std::endl;
    return oss.str();
}

nlohmann::json Level::toJson() const noexcept
{
    nlohmann::json j;
    j["level"] = level;
    j["exp"] = exp;
    j["expToNextLevel"] = expToNextLevel;
    j["progress"] = progress;
    return j;
}