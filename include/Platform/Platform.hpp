#pragma once

#include "User/User.hpp"
#include "Database/SpiritDriver.hpp"
#include "Spirit/Spirit.hpp"
#include "Utils/SpiritUtils.hpp"
#include <hv/HttpServer.h>
#include <iostream>
#include <algorithm>

class Platform : public UserManager
{
private:
    std::vector<SpiritInterface> spiritInfos;
    int spiritNums;
    std::vector<std::unique_ptr<Spirit>> spirits;

public:
    Platform() = default;
    void init() noexcept;
    hv::Json getSpirits() const noexcept;
    int getMaxLevel() const noexcept;
    virtual int registerUser(const std::string &username, const std::string &password) noexcept override;
    ~Platform() = default;
};