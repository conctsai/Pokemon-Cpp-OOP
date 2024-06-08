#pragma once

#include <string>
#include <sstream>
#include "hv/json.hpp"
#include <iostream>

class Description
{
private:
    std::string name;
    std::string description;
    std::string petName;

public:
    Description(const std::string &name, const std::string &description, const std::string &petName) : name(name), description(description), petName(petName){};
    Description(nlohmann::json j) : name(j["name"]), description(j["description"]), petName(j["petName"]){};
    std::string getName() const noexcept { return name; }
    void setPetName(const std::string &name) noexcept { this->petName = name; };
    std::string getDescription() const noexcept { return description; }
    std::string getPetName() const noexcept { return petName; }
    std::string format() const noexcept;
    nlohmann::json toJson() const noexcept;
    virtual ~Description() = default;
};