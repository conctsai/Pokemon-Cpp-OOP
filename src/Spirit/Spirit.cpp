#include "spirit.h"

std::string Spirit::format() const noexcept
{
    return Description::format() + Level::format() + Property::format();
}

bool PowerSpirit::addExp(int exp) noexcept
{
    Property::hp += 10;
    Property::attackPower += 10;
    Property::defensePower += 10;
    Property::speed += 10;
    return true;
}