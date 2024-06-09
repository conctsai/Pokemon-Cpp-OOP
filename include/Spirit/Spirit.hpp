#pragma once

#include "Spirit/Description.hpp"
#include "Spirit/Level.hpp"
#include "Spirit/Property.hpp"
#include "Spirit/Skill.hpp"
#include "hv/json.hpp"
#include "Utils/Utils.hpp"
#include <iostream>
#include <fmt/core.h>

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
                                                60,
                                                105,
                                                60,
                                                95)
    {
        updateSkill();
    };
    Primeape(nlohmann::json j) : PowerSpirit(j)
    {
        basicSkill = std::make_unique<Skill>(j["skills"]["basicSkill"]);
        specialSkill = std::make_unique<Skill>(j["skills"]["specialSkill"]);
        ultimateSkill = std::make_unique<Skill>(j["skills"]["ultimateSkill"]);
    };
    virtual void updateSkill() noexcept override
    {
        SkillCoef = 1.0 + (1.0 / 14) * (level - 1);
        basicSkill = std::make_unique<Skill>(std::string("基础攻击"),
                                             fmt::format("火暴猴用拳头猛击对手，造成攻击力 {} % 的伤害", static_cast<int>(10 * SkillCoef)),
                                             std::vector<SkillEffect>{
                                                 SkillEffect("火爆猴普通攻击",
                                                             {Goal::ENEMY, Type::HP},
                                                             {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-10 * SkillCoef)},
                                                             0,
                                                             0)});
        specialSkill = std::make_unique<Skill>(std::string("恢复"),
                                               fmt::format("火暴猴恢复自身防御力 {} % 的生命值", static_cast<int>(20 * SkillCoef)),
                                               std::vector<SkillEffect>{
                                                   SkillEffect("恢复",
                                                               {Goal::SELF, Type::HP},
                                                               {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(20 * SkillCoef)},
                                                               0,
                                                               0)});
        ultimateSkill = std::make_unique<Skill>(std::string("地球上投"),
                                                fmt::format("火暴猴用拳头猛击对手，造成攻击力 {} % 的伤害，并恢复自身防御力 {} % 的生命值", static_cast<int>(30 * SkillCoef), static_cast<int>(10 * SkillCoef)),
                                                std::vector<SkillEffect>{
                                                    SkillEffect{
                                                        "地球上投",
                                                        {Goal::ENEMY, Type::HP},
                                                        {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-30 * SkillCoef)},
                                                        0,
                                                        0},
                                                    SkillEffect{
                                                        ("地球上投"),
                                                        {Goal::SELF, Type::HP},
                                                        {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(10 * SkillCoef)},
                                                        0,
                                                        0}});
    };
    virtual void levelUp() noexcept override
    {
        PowerSpirit::levelUp();
        updateSkill();
    }
    virtual ~Primeape() override = default;
};

class HPSpirit : public Spirit
{
public:
    HPSpirit(const std::string &name,
             const std::string &description,
             const std::string &petName,
             const int &hp,
             const int &attackPower,
             const int &defensePower,
             const int &speed,
             const int &level = 1,
             const int &exp = 0) : Spirit(name, description, petName, hp, attackPower, defensePower, speed, level, exp){};
    HPSpirit(nlohmann::json j) : Spirit(j){};
    virtual ~HPSpirit() override = default;
    virtual void levelUp() noexcept override;
};

class Eldegoss : public HPSpirit
{
public:
    Eldegoss(std::string petName) : HPSpirit(std::string("白蓬蓬"),
                                             std::string("白蓬蓬是一只植物精灵，它的身体是白色的，头部长有一片白色的花瓣，花瓣上有一颗红色的种子。"),
                                             petName,
                                             70,
                                             50,
                                             90,
                                             60)
    {
        updateSkill();
    };
    Eldegoss(nlohmann::json j) : HPSpirit(j)
    {
        basicSkill = std::make_unique<Skill>(j["skills"]["basicSkill"]);
        specialSkill = std::make_unique<Skill>(j["skills"]["specialSkill"]);
        ultimateSkill = std::make_unique<Skill>(j["skills"]["ultimateSkill"]);
    };
    virtual void updateSkill() noexcept override
    {
        SkillCoef = 1.0 + (1.0 / 14) * (level - 1);
        basicSkill = std::make_unique<Skill>(std::string("基础攻击"),
                                             fmt::format("白蓬蓬用花瓣攻击对手，造成攻击力 {} % 的伤害", static_cast<int>(10 * SkillCoef)),
                                             std::vector<SkillEffect>{
                                                 SkillEffect{"白蓬蓬普通攻击",
                                                             {Goal::ENEMY, Type::HP},
                                                             {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-10 * SkillCoef)},
                                                             0,
                                                             0}});
        specialSkill = std::make_unique<Skill>(std::string("恢复"),
                                               fmt::format("白蓬蓬恢复自身防御力 {} % 的生命值", static_cast<int>(20 * SkillCoef)),
                                               std::vector<SkillEffect>{
                                                   SkillEffect{"恢复",
                                                               {Goal::SELF, Type::HP},
                                                               {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(20 * SkillCoef)},
                                                               0,
                                                               0}});
        ultimateSkill = std::make_unique<Skill>(std::string("种子炸弹"),
                                                fmt::format("白蓬蓬用花瓣攻击对手，造成攻击力 {} % 的伤害，并恢复自身防御力 {} % 的生命值", static_cast<int>(30 * SkillCoef), static_cast<int>(10 * SkillCoef)),
                                                std::vector<SkillEffect>{
                                                    SkillEffect{
                                                        "种子炸弹",
                                                        {Goal::ENEMY, Type::HP},
                                                        {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-30 * SkillCoef)},
                                                        0,
                                                        0},
                                                    SkillEffect{
                                                        ("种子炸弹"),
                                                        {Goal::SELF, Type::HP},
                                                        {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(10 * SkillCoef)},
                                                        0,
                                                        0}});
    };
    virtual void levelUp() noexcept override
    {
        HPSpirit::levelUp();
        updateSkill();
    }
    virtual ~Eldegoss() override = default;
};

class DefenseSpirit : public Spirit
{
public:
    DefenseSpirit(const std::string &name,
                  const std::string &description,
                  const std::string &petName,
                  const int &hp,
                  const int &attackPower,
                  const int &defensePower,
                  const int &speed,
                  const int &level = 1,
                  const int &exp = 0) : Spirit(name, description, petName, hp, attackPower, defensePower, speed, level, exp){};
    DefenseSpirit(nlohmann::json j) : Spirit(j){};
    virtual ~DefenseSpirit() override = default;
    virtual void levelUp() noexcept override;
};

class Shuckle : public DefenseSpirit
{
public:
    Shuckle(std::string petName) : DefenseSpirit(std::string("壶壶"),
                                                 std::string("壶壶是一只虫虫精灵，它的身体是红色的，头部有一个大大的壳，壳上有很多小孔。"),
                                                 petName,
                                                 70,
                                                 50,
                                                 230,
                                                 40)
    {
        updateSkill();
    };
    Shuckle(nlohmann::json j) : DefenseSpirit(j)
    {
        basicSkill = std::make_unique<Skill>(j["skills"]["basicSkill"]);
        specialSkill = std::make_unique<Skill>(j["skills"]["specialSkill"]);
        ultimateSkill = std::make_unique<Skill>(j["skills"]["ultimateSkill"]);
    };
    virtual void updateSkill() noexcept override
    {
        SkillCoef = 1.0 + (1.0 / 14) * (level - 1);
        basicSkill = std::make_unique<Skill>(std::string("基础攻击"),
                                             fmt::format("壶壶用壳攻击对手，造成攻击力 {} % 的伤害", static_cast<int>(10 * SkillCoef)),
                                             std::vector<SkillEffect>{
                                                 SkillEffect{"壶壶普通攻击",
                                                             {Goal::ENEMY, Type::HP},
                                                             {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-10 * SkillCoef)},
                                                             0,
                                                             0}});
        specialSkill = std::make_unique<Skill>(std::string("恢复"),
                                               fmt::format("壶壶恢复自身防御力 {} % 的生命值", static_cast<int>(20 * SkillCoef)),
                                               std::vector<SkillEffect>{
                                                   SkillEffect{"恢复",
                                                               {Goal::SELF, Type::HP},
                                                               {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(20 * SkillCoef)},
                                                               0,
                                                               0}});
        ultimateSkill = std::make_unique<Skill>(std::string("壳之力"),
                                                fmt::format("壶壶用壳攻击对手，造成攻击力 {} % 的伤害，并恢复自身防御力 {} % 的生命值", static_cast<int>(30 * SkillCoef), static_cast<int>(10 * SkillCoef)),
                                                std::vector<SkillEffect>{
                                                    SkillEffect{
                                                        "壳之力",
                                                        {Goal::ENEMY, Type::HP},
                                                        {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-30 * SkillCoef)},
                                                        0,
                                                        0},
                                                    SkillEffect{
                                                        ("壳之力"),
                                                        {Goal::SELF, Type::HP},
                                                        {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(10 * SkillCoef)},
                                                        0,
                                                        0}});
    };
    virtual void levelUp() noexcept override
    {
        DefenseSpirit::levelUp();
        updateSkill();
    }
    virtual ~Shuckle() override = default;
};

class SpeedSpirit : public Spirit
{
public:
    SpeedSpirit(const std::string &name,
                const std::string &description,
                const std::string &petName,
                const int &hp,
                const int &attackPower,
                const int &defensePower,
                const int &speed,
                const int &level = 1,
                const int &exp = 0) : Spirit(name, description, petName, hp, attackPower, defensePower, speed, level, exp){};
    SpeedSpirit(nlohmann::json j) : Spirit(j){};
    virtual ~SpeedSpirit() override = default;
    virtual void levelUp() noexcept override;
};

class Regieleki : public SpeedSpirit
{
public:
    Regieleki(std::string petName) : SpeedSpirit(std::string("雷吉艾基"),
                                                 std::string("雷吉艾基是一只电精灵，它的身体是黄色的，头部有一个大大的圆环，圆环上有很多小孔。"),
                                                 petName,
                                                 50,
                                                 80,
                                                 50,
                                                 100)
    {
        updateSkill();
    };
    Regieleki(nlohmann::json j) : SpeedSpirit(j)
    {
        basicSkill = std::make_unique<Skill>(j["skills"]["basicSkill"]);
        specialSkill = std::make_unique<Skill>(j["skills"]["specialSkill"]);
        ultimateSkill = std::make_unique<Skill>(j["skills"]["ultimateSkill"]);
    };
    virtual void updateSkill() noexcept override
    {
        SkillCoef = 1.0 + (1.0 / 14) * (level - 1);
        basicSkill = std::make_unique<Skill>(std::string("基础攻击"),
                                             fmt::format("雷吉艾基用圆环攻击对手，造成攻击力 {} % 的伤害", static_cast<int>(10 * SkillCoef)),
                                             std::vector<SkillEffect>{
                                                 SkillEffect{"雷吉艾基普通攻击",
                                                             {Goal::ENEMY, Type::HP},
                                                             {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-10 * SkillCoef)},
                                                             0,
                                                             0}});
        specialSkill = std::make_unique<Skill>(std::string("恢复"),
                                               fmt::format("雷吉艾基恢复自身防御力 {} % 的生命值", static_cast<int>(20 * SkillCoef)),
                                               std::vector<SkillEffect>{
                                                   SkillEffect{"恢复",
                                                               {Goal::SELF, Type::HP},
                                                               {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(20 * SkillCoef)},
                                                               0,
                                                               0}});
        ultimateSkill = std::make_unique<Skill>(std::string("雷电之力"),
                                                fmt::format("雷吉艾基用雷电攻击对手，造成攻击力 {} % 的伤害，并恢复自身防御力 {} % 的生命值", static_cast<int>(30 * SkillCoef), static_cast<int>(10 * SkillCoef)),
                                                std::vector<SkillEffect>{
                                                    SkillEffect{
                                                        "雷电之力",
                                                        {Goal::ENEMY, Type::HP},
                                                        {Goal::SELF, Type::ATTACKPOWER, static_cast<int>(-30 * SkillCoef)},
                                                        0,
                                                        0},
                                                    SkillEffect{
                                                        ("雷电之力"),
                                                        {Goal::SELF, Type::HP},
                                                        {Goal::SELF, Type::DEFENSEPOWER, static_cast<int>(10 * SkillCoef)},
                                                        0,
                                                        0}});
    };
    virtual void levelUp() noexcept override
    {
        SpeedSpirit::levelUp();
        updateSkill();
    }
    virtual ~Regieleki() override = default;
};