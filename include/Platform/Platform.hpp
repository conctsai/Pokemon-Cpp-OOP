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
    std::vector<std::unique_ptr<Spirit>> spirits;

public:
    Platform() = default;
    void init() noexcept;
    hv::Json getSpirits() const noexcept;
    void addSpirit(const std::string &spirit_json) noexcept;
    bool renameSpirit(int id, const std::string &name) noexcept;
    bool deleteSpirit(int id) noexcept;
    bool updateSpirit(int id, int exp) noexcept;
    int getMaxLevel() const noexcept;
    virtual int registerUser(const std::string &username, const std::string &password) noexcept override;
    ~Platform() = default;
};

// 只有修改名字，或者增加经验才会改变精灵，所以在执行这两个操作之后，立即Update数据库
// 剩下对数据库的操作就只有新增精灵和删除精灵了