#include <iostream>
#include "Platform/Combat.hpp"
#include "Server/Server.hpp"

int main()
{
    Server s(8080);
    s.run();
}