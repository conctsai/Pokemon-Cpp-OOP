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
        spirits.clear();
        for (int i = 0; i < spiritInfos.size(); i++)
        {
            spirits.push_back(SpiritUtils::getSpirit(hv::Json::parse(spiritInfos[i].spirit_json)));
        }
    }
}

hv::Json Platform::getSpirits() const noexcept
{
    hv::Json j;
    for (int i = 0; i < spiritInfos.size(); i++)
    {
        hv::Json sp;
        sp["id"] = spiritInfos[i].id;
        sp["spirit_json"] = hv::Json::parse(spiritInfos[i].spirit_json);
        j.push_back(sp);
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

void Platform::addSpirit(const std::string &spirit_json) noexcept
{
    SPIRITDRIVER.insertSpirit(this->user.id, spirit_json);
    init();
}

bool Platform::deleteSpirit(int id) noexcept
{
    if (SPIRITDRIVER.deleteSpirit(id))
    {
        init();
        return true;
    }
    else
    {
        return false;
    }
}

bool Platform::renameSpirit(int id, const std::string &name) noexcept
{
    hv::Json spirit_json;
    for (int i = 0; i < spirits.size(); i++)
    {
        if (spiritInfos[i].id == id)
        {
            spirits[i]->setPetName(name);
            spirit_json = spirits[i]->toJson();
            break;
        }
    }
    SPIRITDRIVER.UpdateSpirit(id, spirit_json.dump());
    init();
    return true;
}

bool Platform::updateSpirit(int id, int exp) noexcept
{
    hv::Json spirit_json;
    for (int i = 0; i < spirits.size(); i++)
    {
        if (spiritInfos[i].id == id)
        {
            spirits[i]->addExp(exp);
            spirit_json = spirits[i]->toJson();
            break;
        }
    }
    SPIRITDRIVER.UpdateSpirit(id, spirit_json.dump());
    init();
    return true;
}