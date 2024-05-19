#include "spirit.h"

std::string Spirit::format() const noexcept
{
    return Description::format() + Level::format() + Property::format();
}

void Spirit::addExp(int exp) noexcept
{
    this->exp += exp;
    while (exp >= expToNextLevel)
    {
        level++;
        exp -= expToNextLevel;
        expToNextLevel = EXPTONEXTLEVEL(level);
        levelUp();
    }
    progress = exp * 100 / expToNextLevel;
}

void PowerSpirit::levelUp() noexcept
{
    this->attackPower += utils::get_random_int(4, 7);
    this->defensePower += utils::get_random_int(3, 6);
    this->speed += utils::get_random_int(3, 6);
    this->hp += utils::get_random_int(3, 6);
}