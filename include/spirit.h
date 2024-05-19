#pragma once

#include "description.h"
#include "level.h"
#include "property.h"
#include "utils.h"
#include "skill.h"

class Spirit : public Description, public Level, public Property, public SkillManager
{
public:
    Spirit(const std::string &name,
           const std::string &description,
           const int &hp,
           const int &attackPower,
           const int &defensePower,
           const int &speed,
           const int &level = 1,
           const int &exp = 0) : Description(name, description), Level(level, exp), Property(hp, attackPower, defensePower, speed){};
    std::string format() const noexcept;
    virtual void addExp(int exp) noexcept override;
    virtual ~Spirit() override = default;
};

class PowerSpirit : public Spirit
{
public:
    PowerSpirit(const std::string &name,
                const std::string &description,
                const int &hp,
                const int &attackPower,
                const int &defensePower,
                const int &speed,
                const int &level = 1,
                const int &exp = 0) : Spirit(name, description, hp, attackPower, defensePower, speed, level, exp){};
    virtual ~PowerSpirit() override = default;
    virtual void levelUp() noexcept override;
};

class Primeape : public PowerSpirit
{
public:
    Primeape() : PowerSpirit(std::string("火暴猴"),
                             std::string("火暴猴球状的身体长满了淡黄色的毛。它四肢的被毛消失且戴上了黑色的圆环，手变成了拳套的样子，脚也像人类的脚掌，只是只有两个脚趾。它的尾巴消失了，眼珠变成一条线，额头上一直有发怒隆起的十字青筋。"),
                             65,
                             105,
                             60,
                             95){

                 };
    static std::vector<SkillEffect> basicAttackEffects();
    static std::vector<SkillEffect> specialAttackEffects();
    virtual void updateSkill() noexcept override {};
    virtual ~Primeape() override = default;
};