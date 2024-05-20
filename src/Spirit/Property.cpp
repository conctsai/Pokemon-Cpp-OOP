#include "Spirit/Property.hpp"

std::string Property::format() const noexcept
{
    std::ostringstream oss;
    oss << "{" << std::endl;
    oss << "  \"hp\": " << hp << "," << std::endl;
    oss << "  \"attackPower\": " << attackPower << "," << std::endl;
    oss << "  \"defensePower\": " << defensePower << "," << std::endl;
    oss << "  \"speed\": " << speed << std::endl;
    oss << "}" << std::endl;
    return oss.str();
}