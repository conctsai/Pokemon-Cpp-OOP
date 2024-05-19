#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <memory>

#define GET_TYPE_STRING(e)                                                                            \
    ((e) >= HP && (e) < COUNT ? (e) == HP ? "HP" : (e) == ATTACKPOWER        ? "ATTACKPOWER"          \
                                               : (e) == DEFENSEPOWER         ? "DEFENSEPOWER"         \
                                               : (e) == SPEED                ? "SPEED"                \
                                               : (e) == HP_PERCENT           ? "HP_PERCENT"           \
                                               : (e) == ATTACKPOWER_PERCENT  ? "ATTACKPOWER_PERCENT"  \
                                               : (e) == DEFENSEPOWER_PERCENT ? "DEFENSEPOWER_PERCENT" \
                                               : (e) == SPEED_PERCENT        ? "SPEED_PERCENT"        \
                                                                             : "UNKNOWN"              \
                              : "UNKNOWN")

#define GET_GOAL_STRING(e)                         \
    ((e) == SELF ? "SELF" : (e) == ENEMY ? "ENEMY" \
                                         : "UNKNOWN")

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
    COUNT
};

enum GOAL
{
    SELF,
    ENEMY,
};

struct SkillEffect
{
    Type type;
    int value;
    GOAL goal;
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
    virtual ~SkillManager() = default;
};