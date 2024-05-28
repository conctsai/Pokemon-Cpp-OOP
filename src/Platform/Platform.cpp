#include "Platform/Platform.hpp"

void Platform::init() noexcept
{
    if (!this->is_login)
    {
        exit(-1);
    }
    else
    {
        spiritInfos = SPIRITDRIVER.getSpiritsByUserId(this->user.id);
        for (int i = 0; i < spiritInfos.size(); i++)
        {
            spirits.push_back(SpiritUtils::getSpirit(hv::Json::parse(spiritInfos[i].spirit_json)));
        }
    }
}

hv::Json Platform::getSpirits() const noexcept
{
    hv::Json j;
    for (int i = 0; i < spirits.size(); i++)
    {
        j.push_back(spirits[i]->toJson());
    }
    return j;
}

int Platform::getMaxLevel() const noexcept
{
    auto max_iter = std::max_element(spirits.begin(), spirits.end(), [](const std::unique_ptr<Spirit> &a, const std::unique_ptr<Spirit> &b)
                                     { return a->getLevel() < b->getLevel(); });

    return (*max_iter)->getLevel();
}

int Platform::registerUser(const std::string &username, const std::string &password) noexcept
{
    int id = UserManager::registerUser(username, password);
    if (id == -1)
    {
        return 0;
    }
    else
    {
        SPIRITDRIVER.insertSpirit(id, SpiritUtils::getRandomSpirits(1).dump());
        SPIRITDRIVER.insertSpirit(id, SpiritUtils::getRandomSpirits(1).dump());
        SPIRITDRIVER.insertSpirit(id, SpiritUtils::getRandomSpirits(1).dump());
        return 1; // 注册成功，每个用户注册时赠送3个精灵
    }
}