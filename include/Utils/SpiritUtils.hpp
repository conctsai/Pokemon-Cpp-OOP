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
        else
        {
            exit(-1);
        }
    }

    static nlohmann::json getRandomSpirits(int maxLevel)
    {
        std::unique_ptr<Spirit> spirit = nullptr;
        int type = utils::get_random_int(1, 1);
        if (type == 1)
        {
            spirit = std::make_unique<Primeape>(fmt::format("火暴猴{}", utils::get_random_int(1, 1000)));
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