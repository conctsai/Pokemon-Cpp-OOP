#include "Spirit/Spirit.hpp"

std::string Spirit::format() const noexcept
{
    return "\{\n\"description\": " + Description::format() + ",\n" +
           "\"property\": " + Property::format() + ",\n" +
           "\"level\": " + Level::format() + ",\n" +
           "\"skills\": " + SkillManager::format() + "\n}";
}

void Spirit::addExp(int exp) noexcept
{
    this->exp += exp;
    while (level < 15 && exp >= expToNextLevel)
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

void HPSpirit::levelUp() noexcept
{
    this->attackPower += utils::get_random_int(3, 6);
    this->defensePower += utils::get_random_int(3, 6);
    this->speed += utils::get_random_int(3, 6);
    this->hp += utils::get_random_int(5, 8);
}

void DefenseSpirit::levelUp() noexcept
{
    this->attackPower += utils::get_random_int(3, 6);
    this->defensePower += utils::get_random_int(5, 8);
    this->speed += utils::get_random_int(3, 6);
    this->hp += utils::get_random_int(3, 6);
}

void SpeedSpirit::levelUp() noexcept
{
    this->attackPower += utils::get_random_int(3, 6);
    this->defensePower += utils::get_random_int(3, 6);
    this->speed += utils::get_random_int(5, 8);
    this->hp += utils::get_random_int(3, 6);
}

nlohmann::json Spirit::toJson() const noexcept
{
    nlohmann::json j;
    j["description"] = Description::toJson();
    j["property"] = Property::toJson();
    j["level"] = Level::toJson();
    j["skills"] = SkillManager::toJson();
    return j;
}