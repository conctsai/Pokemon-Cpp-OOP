#pragma once

#include "Spirit/Spirit.hpp"

class SpiritUtils
{
public:
    SpiritUtils() = default;
    ~SpiritUtils() = default;

    static std::unique_ptr<Spirit> getSpirit(nlohmann::json j)
    {
        if (j["description"]["name"] == "火暴猴")
        {
            return std::make_unique<Primeape>(j);
        }
        else if (j["description"]["name"] == "白蓬蓬")
        {
            return std::make_unique<Eldegoss>(j);
        }
        else if (j["description"]["name"] == "壶壶")
        {
            return std::make_unique<Shuckle>(j);
        }
        else if (j["description"]["name"] == "雷吉艾基")
        {
            return std::make_unique<Regieleki>(j);
        }
        else
        {
            exit(-1);
        }
    }

    static nlohmann::json getRandomSpirits(int maxLevel)
    {
        std::unique_ptr<Spirit> spirit = nullptr;
        int type = utils::get_random_int(1, 4);
        if (type == 1)
        {
            spirit = std::make_unique<Primeape>(fmt::format("火暴猴{}", utils::get_random_int(1, 1000)));
        }
        else if (type == 2)
        {
            spirit = std::make_unique<Eldegoss>(fmt::format("白蓬蓬{}", utils::get_random_int(1, 1000)));
        }
        else if (type == 3)
        {
            spirit = std::make_unique<Shuckle>(fmt::format("壶壶{}", utils::get_random_int(1, 1000)));
        }
        else if (type == 4)
        {
            spirit = std::make_unique<Regieleki>(fmt::format("雷吉艾基{}", utils::get_random_int(1, 1000)));
        }
        else
        {
            exit(-1);
        }

        int level = utils::get_random_int(1, maxLevel);
        spirit->addExp((level - 1) * level * (2 * level - 1) / 6);

        return spirit->toJson();
    }
};