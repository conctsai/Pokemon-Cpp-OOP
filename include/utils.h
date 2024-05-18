#pragma once

#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

class utils
{
public:
    utils() = default;
    ~utils() = default;
    static std::string getSHA256(const std::string &text);
};