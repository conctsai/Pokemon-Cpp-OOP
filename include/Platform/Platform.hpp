#pragma once

#include "User/User.hpp"
#include "Database/SpiritDriver.hpp"
#include "Spirit/Spirit.hpp"
#include "Utils/SpiritUtils.hpp"
#include <iostream>

class Platform
{
private:
    UserManager user_manager;
    std::vector<SpiritInterface> spiritInfos;
    int spiritNums;
    std::vector<std::unique_ptr<Spirit>> spirits;

public:
    Platform();
    ~Platform() = default;
};