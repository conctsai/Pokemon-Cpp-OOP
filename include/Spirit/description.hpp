#pragma once

#include <string>
#include <sstream>

class Description
{
private:
    std::string name;
    std::string description;
    std::string petName;

public:
    Description(const std::string &name, const std::string &description, const std::string &petName) : name(name), description(description), petName(petName){};
    std::string getName() const noexcept { return name; }
    std::string getDescription() const noexcept { return description; }
    std::string getPetName() const noexcept { return petName; }
    std::string format() const noexcept;
    virtual ~Description() = default;
};