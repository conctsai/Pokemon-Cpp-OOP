#pragma once
#include <iostream>
#include <string>
#include "Client/ClientHttpDriver.hpp"
#include "Utils/Utils.hpp"
#include <fmt/color.h>

enum Interface
{
    CREATE_SESSION,
    START,
    MAIN,
    LOGIN,
    REGISTER,
    LOGOUT,
    BAG,
    MY_SPIRITS,
    ONLINE_USERS,
    COMBAT,
    MEDALS,
    WIN_RATE,
    EXIT,
};

enum CombatStatus
{
    MODE,
    SELECT,
    FIGHT,
    END,
};

class Client
{
private:
    Interface status;
    int session_id;
    hv::Json spirits;
    ClientHttpDriver http_driver;

public:
    Client(const std::string &url) : http_driver(url)
    {
        status = CREATE_SESSION;
    }
    void run()
    {
        std::string input;
        int maxLevelCount = 0;
        while (true)
        {
            std::cout << "\033[2J";
            std::cout << "\033[1;1H";
            switch (status)
            {
            case CREATE_SESSION:
                session_id = http_driver.get_session_id();
                status = START;
                break;

            case START:
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "         欢迎来到宠物小精灵世界！          \n");
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "            姓名： 蔡正舟\n");
                fmt::print(fmt::fg(fmt::color::purple), "            学号： 2022212010\n");
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "            按下Enter键继续...            \n");
                getchar();
                status = MAIN;
                break;

            case MAIN:
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "                 1. 登录                   \n");
                fmt::print(fmt::fg(fmt::color::purple), "                 2. 注册                   \n");
                fmt::print(fmt::fg(fmt::color::purple), "                 3. 退出                   \n");
                std::cout << "===========================================\n";
                std::cout << "               请选择：";
                switch (getnum(1, 3))
                {
                case 1:
                    status = LOGIN;
                    break;
                case 2:
                    status = REGISTER;
                    break;
                case 3:
                    status = EXIT;
                    break;
                default:
                    break;
                }
                break;

            case LOGIN:
                login() ? status = BAG : status = MAIN;
                getchar();
                break;

            case REGISTER:
                register_user();
                status = MAIN;
                getchar();
                break;

            case BAG:
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "            1. 我的精灵                    \n");
                fmt::print(fmt::fg(fmt::color::purple), "            2. 战斗                        \n");
                fmt::print(fmt::fg(fmt::color::purple), "            3. 在线用户                    \n");
                fmt::print(fmt::fg(fmt::color::purple), "            4. 查看胜率                    \n");
                fmt::print(fmt::fg(fmt::color::purple), "            5. 查看徽章                    \n");
                fmt::print(fmt::fg(fmt::color::purple), "            6. 退出登录                    \n");
                std::cout << "===========================================\n";
                std::cout << "            请选择：";
                switch (getnum(1, 6))
                {
                case 1:
                    status = MY_SPIRITS;
                    break;
                case 2:
                    status = COMBAT;
                    break;
                case 3:
                    status = ONLINE_USERS;
                    break;
                case 4:
                    status = WIN_RATE;
                    break;
                case 5:
                    status = MEDALS;
                    break;
                case 6:
                    status = LOGOUT;
                    break;
                default:
                    break;
                }
                break;

            case MY_SPIRITS:
                spirit();
                status = BAG;
                break;

            case COMBAT:
                combat();
                status = BAG;
                break;

            case MEDALS:
                spirits = http_driver.get_spirits(session_id);
                maxLevelCount = 0;
                for (const auto &spirit : spirits)
                {
                    if (spirit["spirit_json"]["level"]["level"] == 15)
                        maxLevelCount++;
                }
                fmt::print(fmt::fg(fmt::color::yellow), "===========金牌===========");

                fmt::print(fmt::fg(fmt::color::silver), "===========银牌===========");

                fmt::print(fmt::fg(fmt::color::brown), "===========铜牌===========\n");

                if (spirits.size() >= 10)
                {
                    fmt::print(fmt::fg(fmt::color::yellow), "         捕宠高手         ");
                    fmt::print(fmt::fg(fmt::color::silver), "         捕宠能手         ");
                    fmt::print(fmt::fg(fmt::color::brown), "         捕宠新手         \n");
                }
                else if (spirits.size() >= 5)
                {
                    fmt::print(fmt::fg(fmt::color::yellow), "                         ");
                    fmt::print(fmt::fg(fmt::color::silver), "         捕宠能手         ");
                    fmt::print(fmt::fg(fmt::color::brown), "         捕宠新手         \n");
                }
                else if (spirits.size() >= 3)
                {
                    fmt::print(fmt::fg(fmt::color::yellow), "                          ");
                    fmt::print(fmt::fg(fmt::color::silver), "                          ");
                    fmt::print(fmt::fg(fmt::color::brown), "         捕宠新手         \n");
                }

                if (maxLevelCount >= 3)
                {
                    fmt::print(fmt::fg(fmt::color::yellow), "         升级大师         ");
                    fmt::print(fmt::fg(fmt::color::silver), "         升级能手         ");
                    fmt::print(fmt::fg(fmt::color::brown), "         升级新手         \n");
                }
                else if (maxLevelCount >= 1)
                {
                    fmt::print(fmt::fg(fmt::color::yellow), "                         ");
                    fmt::print(fmt::fg(fmt::color::silver), "         升级能手         ");
                    fmt::print(fmt::fg(fmt::color::brown), "         升级新手         \n");
                }
                else
                {
                    fmt::print(fmt::fg(fmt::color::yellow), "                          ");
                    fmt::print(fmt::fg(fmt::color::silver), "                          ");
                    fmt::print(fmt::fg(fmt::color::brown), "         升级新手         \n");
                }
                getchar();
                status = BAG;
                break;

            case ONLINE_USERS:
                online_users();
                status = BAG;
                break;

            case WIN_RATE:
                std::cout << "你的胜率：" << http_driver.get_win_rate(session_id) << "%" << std::endl;
                std::cout << "按下Enter键回到开始界面\n";
                getchar();
                status = BAG;
                break;

            case LOGOUT:
                http_driver.logout(session_id);
                std::cout << "登出成功，按下Enter键回到开始界面\n";
                status = MAIN;
                getchar();
                break;

            case EXIT:
                if (http_driver.exit(session_id))
                {
                    std::cout << "服务器退出成功！，按下Enter关闭程序\n";
                }
                else
                {
                    std::cout << "服务器退出失败！，按下Enter关闭程序\n";
                }
                getchar();
                exit(0);
                break;

            default:
                break;
            }
        }
    }

    bool login()
    {
        std::string username, password;
        std::cout << "===========================================\n";
        fmt::print(fmt::fg(fmt::color::purple), "                  登录                     \n");
        std::cout << "===========================================\n";
        std::cout << "          用户名：";
        getline(std::cin, username);
        std::cout << "          密码：";
        getline(std::cin, password);
        if (http_driver.login(username, password, session_id))
        {
            std::cout << "登录成功！，按下Enter后继续\n";
            return true;
        }
        else
        {
            std::cout << "登录失败！，按下Enter返回开始界面\n";
            return false;
        }
    }

    void register_user()
    {
        std::string username, password;
        std::cout << "===========================================\n";
        fmt::print(fmt::fg(fmt::color::purple), "                 注册                 \n");
        std::cout << "===========================================\n";
        std::cout << "            用户名：";
        getline(std::cin, username);
        std::cout << "            密码：";
        getline(std::cin, password);
        if (http_driver.register_user(username, password, session_id))
        {
            std::cout << "注册成功！，按下Enter返回开始界面\n";
        }
        else
        {
            std::cout << "注册失败！，按下Enter返回开始界面\n";
        }
    }

    void spirit()
    {
        int status = 0;
        std::string input;
        while (true)
        {
            std::cout << "\033[2J";
            std::cout << "\033[1;1H";
            switch (status)
            {
            case 0:
                spirits = http_driver.get_spirits(session_id);
                if (spirits.size() == 0)
                {
                    std::cout << "您还没有精灵！，系统随机赠送一个给您，按下Enter继续\n";
                    http_driver.add_random_spirit(session_id);
                    spirits = http_driver.get_spirits(session_id);
                    getchar();
                }
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "                 我的精灵                 \n");
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::red), "     id      类型      昵称      等级\n");
                for (auto &spirit : spirits)
                {
                    std::cout << "     " << spirit["id"] << "    " << spirit["spirit_json"]["description"]["name"] << "    "
                              << spirit["spirit_json"]["description"]["petName"] << "      " << spirit["spirit_json"]["level"]["level"] << "\n";
                }
                std::cout << std::endl;
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "            1. 查看精灵详情               \n");
                fmt::print(fmt::fg(fmt::color::purple), "            2. 返回主界面                 \n");
                std::cout << "===========================================\n";
                std::cout << "            请选择：";
                if (getnum(1, 2) == 1)
                {
                    std::cout << "请输入精灵id：";
                    getline(std::cin, input);
                    status = 1;
                }
                else
                {
                    return;
                }
                break;
            case 1:
                for (auto &spirit : spirits)
                {
                    if (spirit["id"] == std::stoi(input))
                    {
                        std::cout << "===========================================\n";
                        fmt::print(fmt::fg(fmt::color::purple), "                 精灵详情                 \n");
                        fmt::print(fmt::fg(fmt::color::yellow), "==================描述=====================\n");
                        std::cout << "     id：" << spirit["id"] << "\n";
                        std::cout << "     类型：" << spirit["spirit_json"]["description"]["name"] << "\n";
                        std::cout << "     昵称：" << spirit["spirit_json"]["description"]["petName"] << "\n";
                        std::cout << "     描述：" << spirit["spirit_json"]["description"]["description"] << "\n";
                        fmt::print(fmt::fg(fmt::color::yellow), "==================等级=====================\n");
                        std::cout << "     等级：" << spirit["spirit_json"]["level"]["level"] << "\n";
                        std::cout << " 已获得经验：" << spirit["spirit_json"]["level"]["exp"] << "\n";
                        std::cout << "  升级进程：" << spirit["spirit_json"]["level"]["progress"] << "%\n";
                        fmt::print(fmt::fg(fmt::color::yellow), "==================属性=====================\n");
                        std::cout << "  生命值：" << spirit["spirit_json"]["property"]["hp"] << "\n";
                        std::cout << "  攻击力：" << spirit["spirit_json"]["property"]["attackPower"] << "\n";
                        std::cout << "  防御力：" << spirit["spirit_json"]["property"]["defensePower"] << "\n";
                        std::cout << "  速度：" << spirit["spirit_json"]["property"]["speed"] << "\n";
                        fmt::print(fmt::fg(fmt::color::yellow), "==================技能=====================\n");
                        fmt::print(fmt::fg(fmt::color::red), "普通攻击：{}\n", spirit["spirit_json"]["skills"]["basicSkill"]["description"]);
                        fmt::print(fmt::fg(fmt::color::red), "特殊技能：{}\n", spirit["spirit_json"]["skills"]["specialSkill"]["description"]);
                        fmt::print(fmt::fg(fmt::color::red), "必杀技能：{}\n", spirit["spirit_json"]["skills"]["ultimateSkill"]["description"]);
                        std::cout << "===========================================\n";
                        fmt::print(fmt::fg(fmt::color::purple), "            1. 返回上一级                 \n");
                        fmt::print(fmt::fg(fmt::color::purple), "            2. 更改昵称                   \n");
                        std::cout << "===========================================\n";
                        std::cout << "            请选择：";
                        if (getnum(1, 2) == 1)
                        {
                            status = 0;
                        }
                        else
                        {
                            std::cout << "请输入新昵称：";
                            getline(std::cin, input);
                            http_driver.rename_spirit(session_id, spirit["id"], input);
                            std::cout << "更改成功！，按下Enter返回上一级\n";
                            getchar();
                            status = 0;
                        }
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }

    void combat()
    {
        int status = MODE;
        std::string input;
        hv::Json my_spirit;
        int my_spirit_id;
        hv::Json system_spirits[3];
        hv::Json system_spirit;
        hv::Json fight_result;
        int pve_type;
        int winner;
        int random[3];

        while (true)
        {
            std::cout << "\033[2J";
            std::cout << "\033[1;1H";
            switch (status)
            {
            case MODE:
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "                 战斗模式                 \n");
                std::cout << "===========================================\n";
                fmt::print(fmt::fg(fmt::color::purple), "            1. PVE                        \n");
                fmt::print(fmt::fg(fmt::color::purple), "            2. PVP                        \n");
                fmt::print(fmt::fg(fmt::color::purple), "            3. 返回                        \n");
                std::cout << "===========================================\n";
                std::cout << "            请选择：";
                input = std::to_string(getnum(1, 3));
                if (std::stoi(input) == 1)
                {
                    std::cout << "===========================================\n";
                    fmt::print(fmt::fg(fmt::color::purple), "                 1.升级赛                 \n");
                    fmt::print(fmt::fg(fmt::color::purple), "                 2.决斗赛                 \n");
                    std::cout << "===========================================\n";
                    std::cout << "            请选择：";
                    pve_type = getnum(1, 2);
                    status = SELECT;
                }
                else if (std::stoi(input) == 2)
                {
                    pvp();
                    return;
                }
                else
                {
                    return;
                }
                break;
            case SELECT:
                std::cout << "===========================================\n";
                std::cout << "                PVE                        \n";
                std::cout << "===========================================\n";
                spirits = http_driver.get_spirits(session_id);
                std::cout << "===========================================\n";
                std::cout << "               我的精灵                    \n";
                std::cout << "===========================================\n";
                std::cout << "     id   类型   昵称   等级\n";
                for (auto &spirit : spirits)
                {
                    std::cout << "     " << spirit["id"] << " " << spirit["spirit_json"]["description"]["name"] << " "
                              << spirit["spirit_json"]["description"]["petName"] << " " << spirit["spirit_json"]["level"]["level"] << "\n";
                }
                std::cout << std::endl;
                std::cout << "            请选择出战精灵：";
                getline(std::cin, input);
                for (auto &spirit : spirits)
                {
                    if (spirit["id"] == std::stoi(input))
                    {
                        my_spirit_id = spirit["id"];
                        my_spirit = spirit["spirit_json"];
                        break;
                    }
                }
                std::cout << "===========================================\n";
                std::cout << "            系统精灵                    \n";
                std::cout << "===========================================\n";
                for (int i = 0; i < 3; i++)
                {
                    system_spirit[i] = http_driver.get_system_spirits(session_id);
                    std::cout << "     序号：" << i << " 类型：" << system_spirit[i]["description"]["name"] << " 等级：" << system_spirit[i]["level"]["level"] << "\n";
                }
                std::cout << "            请选择对手：";
                getline(std::cin, input);
                system_spirit = system_spirit[std::stoi(input)];
                std::cout << "===========================================\n";
                std::cout << "            1.开始战斗                    \n";
                std::cout << "            2.返回                        \n";
                std::cout << "===========================================\n";
                getline(std::cin, input);
                if (std::stoi(input) == 1)
                {
                    status = FIGHT;
                }
                else
                {
                    return;
                }
                break;

            case FIGHT:
                fight_result = http_driver.get_combat_result(session_id, my_spirit, system_spirit);
                std::cout << "===========================================\n";
                std::cout << my_spirit["description"]["petName"] << " VS " << system_spirit["description"]["petName"] << "\n";
                std::cout << "昵称：" << my_spirit["description"]["petName"] << "         昵称" << system_spirit["description"]["petName"] << "\n";
                std::cout << "类型：" << my_spirit["description"]["name"] << "         类型" << system_spirit["description"]["name"] << "\n";
                std::cout << "等级：" << my_spirit["level"]["level"] << "         等级" << system_spirit["level"]["level"] << "\n";
                std::cout << "生命：" << my_spirit["property"]["hp"] << "         生命" << system_spirit["property"]["hp"] << "\n";
                std::cout << "攻击：" << my_spirit["property"]["attackPower"] << "         攻击" << system_spirit["property"]["attackPower"] << "\n";
                std::cout << "防御：" << my_spirit["property"]["defensePower"] << "         防御" << system_spirit["property"]["defensePower"] << "\n";
                std::cout << "速度：" << my_spirit["property"]["speed"] << "         速度" << system_spirit["property"]["speed"] << "\n";
                std::cout << "===========================================\n";
                std::cout << "按下Enter开始战斗\n";
                getchar();
                for (auto &round : fight_result["round"])
                {
                    std::cout << "\033[2J";   // ANSI转义序列，用于清屏
                    std::cout << "\033[1;1H"; // ANSI转义序列，用于将光标移动到第1行第1列
                    std::cout << "昵称：" << my_spirit["description"]["petName"] << "         昵称" << system_spirit["description"]["petName"] << "\n";
                    std::cout << "类型：" << my_spirit["description"]["name"] << "         类型" << system_spirit["description"]["name"] << "\n";
                    std::cout << "等级：" << my_spirit["level"]["level"] << "         等级" << system_spirit["level"]["level"] << "\n";
                    std::cout << "生命：" << round["property"][0]["hp"] << "         生命" << round["property"][1]["hp"] << "\n";
                    std::cout << "攻击：" << round["property"][0]["attackPower"] << "         攻击" << round["property"][1]["attackPower"] << "\n";
                    std::cout << "防御：" << round["property"][0]["defensePower"] << "         防御" << round["property"][1]["defensePower"] << "\n";
                    std::cout << "速度：" << round["property"][0]["speed"] << "         速度" << round["property"][1]["speed"] << "\n";
                    std::cout << "===========================================\n";
                    std::cout << round["attack"] << "\n";
                    std::cout << "===========================================\n";
                    for (auto &result : round["result"])
                    {
                        std::cout << result << "\n";
                    }
                    std::cout << "===========================================\n";
                    std::cout << "按下Enter继续\n";
                    getchar();
                }
                winner = fight_result["winner"];
                std::cout << fight_result["fighter"][winner] << "获胜！\n";
                std::cout << "按下Enter进入结算界面\n";
                getchar();
                status = END;
                break;

            case END:
                if (pve_type == 1)
                {
                    if (winner == 0)
                    {
                        std::cout << "升级赛胜利！，你的精灵获得了50点经验\n";
                        http_driver.update_win(session_id, true);
                        std::cout << "==================升级前====================\n";
                        std::cout << "     等级：" << my_spirit["level"]["level"] << "\n";
                        std::cout << " 已获得经验：" << my_spirit["level"]["exp"] << "\n";
                        std::cout << "  升级进程：" << my_spirit["level"]["progress"] << "%\n";
                        std::cout << "  攻击力：" << my_spirit["property"]["attackPower"] << "\n";
                        std::cout << "  防御力：" << my_spirit["property"]["defensePower"] << "\n";
                        std::cout << "  速度：" << my_spirit["property"]["speed"] << "\n";
                        std::cout << "  生命值：" << my_spirit["property"]["hp"] << "\n";
                        http_driver.level_up(session_id, my_spirit_id, 50);
                        spirits = http_driver.get_spirits(session_id);
                        std::cout << "==================升级后====================\n";
                        for (auto &spirit : spirits)
                        {
                            if (spirit["id"] == my_spirit_id)
                            {
                                my_spirit = spirit["spirit_json"];
                                break;
                            }
                        }
                        std::cout << "     等级：" << my_spirit["level"]["level"] << "\n";
                        std::cout << " 已获得经验：" << my_spirit["level"]["exp"] << "\n";
                        std::cout << "  升级进程：" << my_spirit["level"]["progress"] << "%\n";
                        std::cout << "  攻击力：" << my_spirit["property"]["attackPower"] << "\n";
                        std::cout << "  防御力：" << my_spirit["property"]["defensePower"] << "\n";
                        std::cout << "  速度：" << my_spirit["property"]["speed"] << "\n";
                        std::cout << "  生命值：" << my_spirit["property"]["hp"] << "\n";
                        std::cout << "按下Enter返回\n";
                        getchar();
                        return;
                    }
                    else
                    {
                        std::cout << "升级赛失败！\n";
                        http_driver.update_win(session_id, false);
                        std::cout << "按下Enter返回\n";
                        getchar();
                        return;
                    }
                }
                else if (pve_type == 2)
                {
                    if (winner == 0)
                    {
                        std::cout << "决斗赛胜利！，你获得了系统精灵" << system_spirit["description"]["petName"] << "\n";
                        http_driver.update_win(session_id, true);
                        std::cout << "=============获得前================\n";
                        std::cout << "===========================================\n";
                        std::cout << "            我的精灵                    \n";
                        std::cout << "===========================================\n";
                        std::cout << "     id   类型   昵称   等级\n";
                        for (auto &spirit : spirits)
                        {
                            std::cout << "     " << spirit["id"] << " " << spirit["spirit_json"]["description"]["name"] << " "
                                      << spirit["spirit_json"]["description"]["petName"] << " " << spirit["spirit_json"]["level"]["level"] << "\n";
                        }
                        std::cout << std::endl;
                        http_driver.add_spirit(session_id, system_spirit);
                        spirits = http_driver.get_spirits(session_id);
                        std::cout << "==================获得后====================\n";
                        std::cout << "===========================================\n";
                        std::cout << "            我的精灵                    \n";
                        std::cout << "===========================================\n";
                        std::cout << "     id   类型   昵称   等级\n";
                        for (auto &spirit : spirits)
                        {
                            std::cout << "     " << spirit["id"] << " " << spirit["spirit_json"]["description"]["name"] << " "
                                      << spirit["spirit_json"]["description"]["petName"] << " " << spirit["spirit_json"]["level"]["level"] << "\n";
                        }
                        std::cout << std::endl;
                        std::cout << "按下Enter返回\n";
                        getchar();
                        return;
                    }
                    else if (winner == 1)
                    {
                        std::cout << "决斗赛失败！\n";
                        http_driver.update_win(session_id, false);
                        std::cout << "请从下列你的精灵中选择一个送出  \n";
                        // 从我的精灵中随机选择3个送出
                        std::cout << "     id   类型   昵称   等级\n";
                        if (spirits.size() < 3)
                        {
                            for (auto &spirit : spirits)
                            {
                                std::cout << "     " << spirit["id"] << " " << spirit["spirit_json"]["description"]["name"] << " "
                                          << spirit["spirit_json"]["description"]["petName"] << " " << spirit["spirit_json"]["level"]["level"] << "\n";
                            }
                        }
                        else
                        {
                            for (int i = 0; i < 3; i++)
                            {
                                random[i] = utils::get_random_int(0, spirits.size() - 1);
                                for (int j = 0; j < i; j++)
                                {
                                    if (random[i] == random[j])
                                    {
                                        i--;
                                        break;
                                    }
                                }
                            }

                            for (int i = 0; i < 3; i++)
                            {
                                std::cout << "     " << spirits[random[i]]["id"] << " " << spirits[random[i]]["spirit_json"]["description"]["name"] << " "
                                          << spirits[random[i]]["spirit_json"]["description"]["petName"] << " " << spirits[random[i]]["spirit_json"]["level"]["level"] << "\n";
                            }
                        }
                        std::cout << "请选择：";
                        getline(std::cin, input);
                        http_driver.delete_spirit(session_id, stoi(input));
                        std::cout << "送出成功！\n";
                        std::cout << "按下Enter返回\n";
                        getchar();
                        return;
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }

    void pvp()
    {
        std::string input;
        hv::Json my_spirit;
        int status = 0;
        while (true)
        {
            std::cout << "\033[2J";   // ANSI转义序列，用于清屏
            std::cout << "\033[1;1H"; // ANSI转义序列，用于将光标移动到第1行第1列
            switch (status)
            {
            case 0:
                std::cout << "===========================================\n";
                std::cout << "            PVP                        \n";
                std::cout << "===========================================\n";
                spirits = http_driver.get_spirits(session_id);
                std::cout << "===========================================\n";
                std::cout << "            我的精灵                    \n";
                std::cout << "===========================================\n";
                std::cout << "     id   类型   昵称   等级\n";
                for (auto &spirit : spirits)
                {
                    std::cout << "     " << spirit["id"] << " " << spirit["spirit_json"]["description"]["name"] << " "
                              << spirit["spirit_json"]["description"]["petName"] << " " << spirit["spirit_json"]["level"]["level"] << "\n";
                }
                std::cout << std::endl;
                std::cout << "            请选择出战精灵：";
                getline(std::cin, input);
                for (auto &spirit : spirits)
                {
                    if (spirit["id"] == std::stoi(input))
                    {
                        my_spirit = spirit["spirit_json"];
                        break;
                    }
                }
                std::cout << "按下Enter键加入匹配队列";
                std::cout << session_id << std::endl;
                std::cout << std::stoi(input) << std::endl;
                http_driver.join_match(session_id, std::stoi(input));
                status = 1;
                break;

            case 1:
                std::cout << "等待匹配中...\n";
                while (true)
                {
                    std::pair<bool, hv::Json> match = http_driver.get_match(session_id);
                    if (match.first)
                    {
                        std::cout << "匹配成功！\n";
                        std::cout << "对手用户名：" << match.second["enemy"] << "\n";
                        std::cout << "对手精灵信息：\n";
                        std::cout << "     类型：" << match.second["enemy_spirit"]["description"]["name"] << "\n";
                        std::cout << "     昵称：" << match.second["enemy_spirit"]["description"]["petName"] << "\n";
                        std::cout << "     等级：" << match.second["enemy_spirit"]["level"]["level"] << "\n";
                        std::cout << "     生命：" << match.second["enemy_spirit"]["property"]["hp"] << "\n";
                        std::cout << "     攻击：" << match.second["enemy_spirit"]["property"]["attackPower"] << "\n";
                        std::cout << "     防御：" << match.second["enemy_spirit"]["property"]["defensePower"] << "\n";
                        std::cout << "     速度：" << match.second["enemy_spirit"]["property"]["speed"] << "\n";
                        std::cout << "按下Enter开始战斗\n";
                        getchar();
                        for (auto &round : match.second["result"]["round"])
                        {
                            std::cout << "\033[2J";   // ANSI转义序列，用于清屏
                            std::cout << "\033[1;1H"; // ANSI转义序列，用于将光标移动到第1行第1列
                            std::cout << "昵称：" << my_spirit["description"]["petName"] << "         昵称" << match.second["enemy_spirit"]["description"]["petName"] << "\n";
                            std::cout << "类型：" << my_spirit["description"]["name"] << "         类型" << match.second["enemy_spirit"]["description"]["name"] << "\n";
                            std::cout << "等级：" << my_spirit["level"]["level"] << "         等级" << match.second["enemy_spirit"]["level"]["level"] << "\n";
                            std::cout << "生命：" << round["property"][0]["hp"] << "         生命" << round["property"][1]["hp"] << "\n";
                            std::cout << "攻击：" << round["property"][0]["attackPower"] << "         攻击" << round["property"][1]["attackPower"] << "\n";
                            std::cout << "防御：" << round["property"][0]["defensePower"] << "         防御" << round["property"][1]["defensePower"] << "\n";
                            std::cout << "速度：" << round["property"][0]["speed"] << "         速度" << round["property"][1]["speed"] << "\n";
                            std::cout << "===========================================\n";
                            std::cout << round["attack"] << "\n";
                            std::cout << "===========================================\n";
                            for (auto &result : round["result"])
                            {
                                std::cout << result << "\n";
                            }
                            std::cout << "===========================================\n";
                            std::cout << "按下Enter继续\n";
                            getchar();
                        }
                        std::cout << match.second["result"]["fighter"][static_cast<int>(match.second["result"]["winner"])] << "获胜！\n";
                        std::cout << "按下Enter返回\n";
                        getchar();
                        return;
                        break;
                    }
                    else
                    {
                        sleep(1);
                    }
                }
                break;

            default:
                break;
            }
        }
    }

    void online_users()
    {
        hv::Json users = http_driver.get_all_user(session_id);
        int status = 0;
        int id = 0;
        std::string input;
        while (true)
        {
            std::cout << "\033[2J";   // ANSI转义序列，用于清屏
            std::cout << "\033[1;1H"; // ANSI转义序列，用于将光标移动到第1行第1列
            switch (status)
            {
            case 0:
                std::cout << "===========================================\n";
                std::cout << "            在线用户                    \n";
                std::cout << "===========================================\n";
                std::cout << "    序号    用户名   精灵数量   是否在线\n";
                for (auto &user : users)
                {
                    std::cout << "    " << user["id"] << "    " << user["username"] << "    " << user["spirits"].size() << "    " << user["online"] << "\n";
                }
                std::cout << "       1.查看用户详情\n";
                std::cout << "       2.返回\n";
                std::cout << "===========================================\n";
                std::cout << "请选择：";
                getline(std::cin, input);
                if (std::stoi(input) == 1)
                {
                    std::cout << "请输入序号：";
                    getline(std::cin, input);
                    id = std::stoi(input);
                    status = 1;
                }
                else
                {
                    return;
                }
                break;
            case 1:
                std::cout << "===========================================\n";
                std::cout << "            用户详情                    \n";
                std::cout << "===========================================\n";
                for (auto &user : users)
                {
                    if (user["id"] == id)
                    {
                        std::cout << "    用户名：" << user["username"] << "\n";
                        std::cout << "    精灵数量：" << user["spirits"].size() << "\n";
                        std::cout << "    是否在线：" << user["online"] << "\n";
                        std::cout << "    精灵列表：\n";
                        for (auto &spirit : user["spirits"])
                        {
                            std::cout << "        " << spirit["description"]["name"] << " " << spirit["description"]["petName"] << " " << spirit["level"]["level"] << "\n";
                            std::cout << "        " << "生命：" << spirit["property"]["hp"] << " 攻击：" << spirit["property"]["attackPower"] << " 防御：" << spirit["property"]["defensePower"] << " 速度：" << spirit["property"]["speed"] << "\n";
                        }
                        std::cout << "===========================================\n";
                        std::cout << "按下Enter返回\n";
                        getchar();
                        status = 0;
                    }
                }
                break;
            default:
                break;
            }
        }
    }

    int getnum(int min, int max)
    {
        std::string input;
        while (true)
        {
            getline(std::cin, input);
            try
            {
                int num = std::stoi(input);
                if (num >= min && num <= max)
                {
                    return num;
                }
                else
                {
                    std::cout << "输入错误，请重新输入：";
                }
            }
            catch (std::exception &e)
            {
                std::cout << "输入错误，请重新输入：";
            }
        }
    }

    ~Client() = default;
};