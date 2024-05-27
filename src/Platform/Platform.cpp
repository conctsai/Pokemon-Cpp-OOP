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