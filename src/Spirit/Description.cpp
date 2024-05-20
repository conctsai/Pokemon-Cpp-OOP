#include "description.hpp"

std::string Description::format() const noexcept
{
    std::ostringstream oss;
    oss << "{" << std::endl;
    oss << "  \"name\": \"" << name << "\"," << std::endl;
    oss << "  \"description\": \"" << description << "\"" << std::endl;
    oss << "}" << std::endl;
    return oss.str();
}