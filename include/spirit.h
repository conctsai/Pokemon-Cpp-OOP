#pragma once

#include "description.h"
#include "level.h"
#include "property.h"

class Spirit : public Description, public Level, public Property
{
public:
    Spirit(const std::string &name,
           const std::string &description,
           const int &level,
           const int &exp,
           const int &hp,
           const int &attackPower,
           const int &defensePower,
           const int &speed) : Description(name, description), Level(level, exp), Property(hp, attackPower, defensePower, speed){};
    Spirit(const std::string &name,
           const std::string &description,
           const int &hp,
           const int &attackPower,
           const int &defensePower,
           const int &speed) : Description(name, description), Property(hp, attackPower, defensePower, speed){};
    std::string format() const noexcept;
    virtual ~Spirit() override = default;
};

class PowerSpirit : public Spirit
{
public:
    PowerSpirit(const std::string &name,
                const std::string &description,
                const int &level,
                const int &exp,
                const int &hp,
                const int &attackPower,
                const int &defensePower,
                const int &speed) : Spirit(name, description, level, exp, hp, attackPower, defensePower, speed){};
    PowerSpirit(const std::string &name,
                const std::string &description,
                const int &hp,
                const int &attackPower,
                const int &defensePower,
                const int &speed) : Spirit(name, description, hp, attackPower, defensePower, speed){};
    virtual ~PowerSpirit() override = default;
    virtual bool addExp(int exp) noexcept override;
};

class Primeape : public PowerSpirit
{
public:
    Primeape() : PowerSpirit(std::string("火暴猴"),
                             std::string("火暴猴球状的身体长满了淡黄色的毛。它四肢的被毛消失且戴上了黑色的圆环，手变成了拳套的样子，脚也像人类的脚掌，只是只有两个脚趾。它的尾巴消失了，眼珠变成一条线，额头上一直有发怒隆起的十字青筋。"),
                             65,
                             105,
                             60,
                             95){};
    virtual ~Primeape() override = default;
};

// class PowerSpirit : public Spirit
// {
// public:
//     PowerSpirit(const std::string &name, const Level &level, const Property &property) : Spirit(name, level, property){};
//     virtual ~PowerSpirit() override = default;
// };

// class HealthSpirit : public Spirit
// {
// public:
//     HealthSpirit(const std::string &name, const Level &level, const Property &property) : Spirit(name, level, property){};
//     virtual ~HealthSpirit() override = default;
// };

// class DefenseSpirit : public Spirit
// {
// public:
//     DefenseSpirit(const std::string &name, const Level &level, const Property &property) : Spirit(name, level, property){};
//     virtual ~DefenseSpirit() override = default;
// };

// class SpeedSpirit : public Spirit
// {
// public:
//     SpeedSpirit(const std::string &name, const Level &level, const Property &property) : Spirit(name, level, property){};
//     virtual ~SpeedSpirit() override = default;
// };