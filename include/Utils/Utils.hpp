#pragma once

#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include "Spirit/Skill.hpp"

class utils
{
public:
    utils() = default;
    ~utils() = default;
    static std::string getSHA256(const std::string &text);
    static int get_random_int(int min, int max);
    static bool SkillEffectComparator(SkillEffect a, SkillEffect b);
};