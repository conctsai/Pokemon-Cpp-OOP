#include "Platform/Platform.hpp"

Platform::Platform()
{
    std::string username;
    std::string password;
    while (true)
    {
        std::cout << "输入用户名：" << std::endl;
        std::cin >> username;
        std::cout << "输入密码：" << std::endl;
        std::cin >> password;

        user_manager.login(username, password);

        if (user_manager.getLoginStatus())
        {
            std::cout << "登录成功" << std::endl;
            break;
        }
        else
        {
            std::cout << "登录失败，请重新登录" << std::endl
                      << std::endl;
        }
    }

    spiritInfos = SPIRITDRIVER.getAllSpirits();
    spiritNums = spiritInfos.size();

    for (int i = 0; i < spiritNums; i++)
    {
        spirits.push_back(SpiritUtils::getSpirit(nlohmann::json::parse(spiritInfos[i].spirit_json)));
    }

    std::cout << "您有" << spiritNums << "个精灵" << std::endl;

    for (int i = 0; i < spiritNums; i++)
    {
        std::cout << spirits[i]->toJson().dump();
    }
}