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
};