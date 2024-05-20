#pragma once
#include <string>
#include <sstream>

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
    int getLevel() const noexcept { return level; }
    int getExp() const noexcept { return exp; }
    virtual void addExp(int exp) noexcept = 0;
    virtual void levelUp() noexcept = 0;
    std::string format() const noexcept;
    virtual ~Level() = default;
};