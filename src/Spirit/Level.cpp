#include "Spirit/level.hpp"

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