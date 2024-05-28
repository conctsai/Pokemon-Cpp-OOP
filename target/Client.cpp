#include "Platform/Platform.hpp"
#include <iostream>

int main()
{
    Platform platform;
    platform.login("conc", "123456");
    platform.init();
    std::cout << platform.getMaxLevel();
}