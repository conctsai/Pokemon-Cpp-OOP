#pragma once

#include "Spirit/Description.hpp"
#include "Spirit/Level.hpp"
#include "Spirit/Property.hpp"
#include "Utils/Utils.hpp"
#include "Spirit/Skill.hpp"
#include "Utils/Json.hpp"
#include <iostream>

class Spirit : public Description, public Level, public Property, public SkillManager
{
public:
    Spirit(const std::string &name,
           const std::string &description,
           const std::string &petName,
           const int &hp,
           const int &attackPower,
           const int &defensePower,
           const int &speed,
           const int &level = 1,
           const int &exp = 0) : Description(name, description, petName), Level(level, exp), Property(hp, attackPower, defensePower, speed){};
    Spirit(nlohmann::json j) : Description(j["description"]), Level(j["level"]), Property(j["property"]){};
    std::string format() const noexcept;
    nlohmann::json toJson() const noexcept;
    virtual void addExp(int exp) noexcept override;
    virtual void levelUp() noexcept override {};
    virtual void updateSkill() noexcept override {};
    virtual ~Spirit() override = default;
};

class PowerSpirit : public Spirit
{
public:
    PowerSpirit(const std::string &name,
                const std::string &description,
                const std::string &petName,
                const int &hp,
                const int &attackPower,
                const int &defensePower,
                const int &speed,
                const int &level = 1,
                const int &exp = 0) : Spirit(name, description, petName, hp, attackPower, defensePower, speed, level, exp){};
    PowerSpirit(nlohmann::json j) : Spirit(j){};
    virtual ~PowerSpirit() override = default;
    virtual void levelUp() noexcept override;
};

class Primeape : public PowerSpirit
{
public:
    Primeape(std::string petName) : PowerSpirit(std::string("火暴猴"),
                                                std::string("火暴猴球状的身体长满了淡黄色的毛。它四肢的被毛消失且戴上了黑色的圆环，手变成了拳套的样子，脚也像人类的脚掌，只是只有两个脚趾。它的尾巴消失了，眼珠变成一条线，额头上一直有发怒隆起的十字青筋。"),
                                                petName,
                                                65,
                                                105,
                                                60,
                                                95)
    {
        basicSkill = std::make_unique<Skill>(std::string("基础攻击"),
                                             std::string("火暴猴用拳头猛击对手，造成攻击力10%的伤害"),
                                             std::vector<SkillEffect>{
                                                 SkillEffect("火爆猴普通攻击",
                                                             {Goal::ENEMY, Type::HP},
                                                             {Goal::SELF, Type::ATTACKPOWER, -10},
                                                             0,
                                                             0)});
        specialSkill = std::make_unique<Skill>(std::string("恢复"),
                                               std::string("恢复防御力20%的生命值"),
                                               std::vector<SkillEffect>{
                                                   SkillEffect("恢复",
                                                               {Goal::SELF, Type::HP},
                                                               {Goal::SELF, Type::DEFENSEPOWER, 20},
                                                               0,
                                                               0)});
        ultimateSkill = std::make_unique<Skill>(std::string("地球上投"),
                                                std::string("火暴猴用拳头猛击对手，造成攻击力30%的伤害，并恢复自身防御力10%的生命值"),
                                                std::vector<SkillEffect>{
                                                    SkillEffect("地球上投",
                                                                {Goal::ENEMY, Type::HP},
                                                                {Goal::SELF, Type::ATTACKPOWER, -30},
                                                                0,
                                                                0),
                                                    SkillEffect(("地球上投"),
                                                                {Goal::SELF, Type::HP},
                                                                {Goal::SELF, Type::DEFENSEPOWER, 10},
                                                                0,
                                                                0)});
    };
    Primeape(nlohmann::json j) : PowerSpirit(j)
    {
        basicSkill = std::make_unique<Skill>(j["skills"]["basicSkill"]);
        specialSkill = std::make_unique<Skill>(j["skills"]["specialSkill"]);
        ultimateSkill = std::make_unique<Skill>(j["skills"]["ultimateSkill"]);
    };
    virtual void updateSkill() noexcept override {};
    virtual ~Primeape() override = default;
};