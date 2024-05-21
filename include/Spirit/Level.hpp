#pragma once
#include <string>
#include <sstream>
#include "Utils/Json.hpp"

#define EXPTONEXTLEVEL(level) (level * level)

class Level
{
protected:
    int level;
    int exp;
    int expToNextLevel;
    int progress;

public:
    Level(int level, int exp) : level(level), exp(exp)
    {
        expToNextLevel = EXPTONEXTLEVEL(level);
        progress = exp * 100 / expToNextLevel;
    };
    Level(nlohmann::json j) : level(j["level"]), exp(j["exp"])
    {
        expToNextLevel = EXPTONEXTLEVEL(level);
        progress = exp * 100 / expToNextLevel;
    };
    int getLevel() const noexcept { return level; }
    int getExp() const noexcept { return exp; }
    virtual void addExp(int exp) noexcept {};
    virtual void levelUp() noexcept {};
    std::string format() const noexcept;
    nlohmann::json toJson() const noexcept;
    virtual ~Level() = default;
};