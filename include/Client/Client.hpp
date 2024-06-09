#pragma once
#include <iostream>
#include <string>
#include "Client/ClientHttpDriver.hpp"

enum Interface
{
    CREATE_SESSION,
    START,
    MAIN,
    LOGIN,
    REGISTER,
    BAG,
    EXIT,
};

class Client
{
private:
    Interface status;
    int session_id;
    ClientHttpDriver http_driver;

public:
    Client(const std::string &url) : http_driver(url)
    {
        status = CREATE_SESSION;
    }
    void run()
    {
        std::string input;
        while (true)
        {
            std::cout << "\033[2J";   // ANSI转义序列，用于清屏
            std::cout << "\033[1;1H"; // ANSI转义序列，用于将光标移动到第1行第1列
            switch (status)
            {
            case CREATE_SESSION:
                session_id = http_driver.get_session_id();
                status = START;
                break;

            case START:
                std::cout << "===========================================\n";
                std::cout << "         欢迎来到宠物小精灵世界！          \n";
                std::cout << "===========================================\n";
                std::cout << "            姓名：" << "蔡正舟" << "\n";
                std::cout << "            学号：" << "2022212010" << "\n";
                std::cout << "===========================================\n";
                std::cout << "            按下Enter键继续...            \n";
                getchar();
                status = MAIN;
                break;

            case MAIN:
                std::cout << "===========================================\n";
                std::cout << "            1. 登录                        \n";
                std::cout << "            2. 注册                        \n";
                std::cout << "            3. 退出                        \n";
                std::cout << "===========================================\n";
                std::cout << "            请选择：";
                getline(std::cin, input);
                switch (std::stoi(input))
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
        std::cout << "            登录                        \n";
        std::cout << "===========================================\n";
        std::cout << "            用户名：";
        getline(std::cin, username);
        std::cout << "            密码：";
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
        std::cout << "            注册                        \n";
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
    ~Client() = default;
};