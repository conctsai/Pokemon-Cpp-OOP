#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <memory>

#define GET_GOAL_STRING(goal) \
    (goal == SELF ? "\"SELF\"" : (goal == ENEMY ? "\"ENEMY\"" : "\"UNKNOWN\""))

#define GET_TYPE_STRING(type) \
    (type == HP ? "\"HP\"" : (type == ATTACKPOWER ? "\"ATTACKPOWER\"" : (type == DEFENSEPOWER ? "\"DEFENSEPOWER\"" : (type == SPEED ? "\"SPEED\"" : (type == HP_PERCENT ? "\"HP_PERCENT\"" : (type == ATTACKPOWER_PERCENT ? "\"ATTACKPOWER_PERCENT\"" : (type == DEFENSEPOWER_PERCENT ? "\"DEFENSEPOWER_PERCENT\"" : (type == SPEED_PERCENT ? "\"SPEED_PERCENT\"" : (type == FIX_VALUE ? "\"FIX_VALUE\"" : "\"UNKNOWN\"")))))))))

enum Type
{
    HP,
    ATTACKPOWER,
    DEFENSEPOWER,
    SPEED,
    HP_PERCENT,
    ATTACKPOWER_PERCENT,
    DEFENSEPOWER_PERCENT,
    SPEED_PERCENT,
    FIX_VALUE,
};

enum Goal
{
    SELF,
    ENEMY,
};

struct Target
{
    Goal goal;
    Type type;
};

struct Source
{
    Goal goal;
    Type type;
    int value;
};

struct SkillEffect
{
    std::string description;
    Target target;
    Source source;
    int activationTime;
    int duration;
};

class Skill
{
private:
    std::string name;
    std::string description;
    std::vector<SkillEffect> effects;

public:
    Skill(const std::string &name, const std::string &description, const std::vector<SkillEffect> &effects) : name(name), description(description), effects(effects){};
    Skill(const Skill &skill) = default;
    Skill(Skill &&skill) = default;
    std::vector<SkillEffect> getEffects() const noexcept { return effects; }
    std::string format() const noexcept;
    ~Skill() = default;
};

class SkillManager
{
protected:
    std::unique_ptr<Skill> basicSkill;
    std::unique_ptr<Skill> specialSkill;
    std::unique_ptr<Skill> ultimateSkill;

public:
    SkillManager() = default;
    virtual void updateSkill() noexcept = 0;
    std::string format() const noexcept;
    virtual ~SkillManager() = default;
};