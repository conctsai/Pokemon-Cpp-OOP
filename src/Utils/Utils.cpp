#include "utils.hpp"

std::string utils::getSHA256(const std::string &text)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)text.c_str(), text.length(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int utils::get_random_int(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

bool utils::SkillEffectComparator(SkillEffect a, SkillEffect b)
{
    return a.activationTime < b.activationTime;
}