#pragma once

#include <string>
#include <sstream>

class Description
{
private:
    std::string name;
    std::string description;

public:
    Description(const std::string name, const std::string description) : name(name), description(description){};
    std::string getName() const noexcept { return name; }
    std::string getDescription() const noexcept { return description; }
    std::string format() const noexcept;
    virtual ~Description() = default;
};