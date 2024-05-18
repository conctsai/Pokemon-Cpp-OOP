#pragma once
#include <string>
#include <sstream>

class Level
{
protected:
    int level;
    int exp;

public:
    Level(int level, int exp) : level(level), exp(exp){};
    Level() = default;
    int getLevel() const noexcept { return level; }
    int getExp() const noexcept { return exp; }
    virtual bool addExp(int exp) noexcept = 0;
    std::string format() const noexcept;
    virtual ~Level() = default;
};