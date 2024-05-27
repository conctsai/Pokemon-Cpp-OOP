#include "hv/hv.h"
#include <iostream>
int main()
{
    std::cout << hv_compile_version() << std::endl;
}