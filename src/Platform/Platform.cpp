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
            spirits.push_back(SpiritUtils::getSpirit(spiritInfos[i].spirit_json));
        }
    }
}