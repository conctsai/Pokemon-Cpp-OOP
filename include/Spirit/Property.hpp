#pragma once
#include <string>
#include <sstream>

#include "hv/json.hpp"

class Property
{
protected:
    int hp;
    int hp_old;
    int attackPower;
    int attackPower_old;
    int defensePower;
    int defensePower_old;
    int speed;
    int speed_old;

public:
    Property(int hp, int attackPower, int defensePower, int speed) : hp(hp), attackPower(attackPower), defensePower(defensePower), speed(speed){};
    Property(nlohmann::json j) : hp(j["hp"]), attackPower(j["attackPower"]), defensePower(j["defensePower"]), speed(j["speed"]){};
    int getHp() const noexcept { return hp; }
    int getAttackPower() const noexcept { return attackPower; }
    int getDefensePower() const noexcept { return defensePower; }
    int getSpeed() const noexcept { return speed; }
    int getHpOld() const noexcept { return hp_old; }
    int getAttackPowerOld() const noexcept { return attackPower_old; }
    int getDefensePowerOld() const noexcept { return defensePower_old; }
    int getSpeedOld() const noexcept { return speed_old; }
    void setHp(int hp) noexcept
    {
        this->hp_old = this->hp;
        this->hp = hp;
    }
    void setAttackPower(int attackPower) noexcept
    {
        this->attackPower_old = this->attackPower;
        this->attackPower = attackPower;
    }
    void setDefensePower(int defensePower) noexcept
    {
        this->defensePower_old = this->defensePower;
        this->defensePower = defensePower;
    }
    void setSpeed(int speed) noexcept
    {
        this->speed_old = this->speed;
        this->speed = speed;
    }
    std::string format() const noexcept;
    nlohmann::json toJson() const noexcept;
    virtual ~Property() = default;
};