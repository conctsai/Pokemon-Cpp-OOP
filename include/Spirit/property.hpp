#pragma once
#include <string>
#include <sstream>

class Property
{
protected:
    int hp;
    int attackPower;
    int defensePower;
    int speed;

public:
    Property(int hp, int attackPower, int defensePower, int speed) : hp(hp), attackPower(attackPower), defensePower(defensePower), speed(speed){};
    int getHp() const noexcept { return hp; }
    int getAttackPower() const noexcept { return attackPower; }
    int getDefensePower() const noexcept { return defensePower; }
    int getSpeed() const noexcept { return speed; }
    void setHp(int hp) noexcept { this->hp = hp; }
    void setAttackPower(int attackPower) noexcept { this->attackPower = attackPower; }
    void setDefensePower(int defensePower) noexcept { this->defensePower = defensePower; }
    void setSpeed(int speed) noexcept { this->speed = speed; }
    std::string format() const noexcept;
    virtual ~Property() = default;
};