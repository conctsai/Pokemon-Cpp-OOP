#pragma once

#include "spirit.hpp"
#include <memory>
#include <queue>
#include <vector>
#include <iostream>
#include <functional>

class Combat
{
private:
    std::unique_ptr<Spirit> spirit1;
    std::unique_ptr<Spirit> spirit2;
    std::vector<std::vector<SkillEffect>> spirit1SkillEffects;
    std::vector<std::vector<SkillEffect>> spirit2SkillEffects;
    std::queue<SkillEffect> skillQueue1;
    std::queue<SkillEffect> skillQueue2;

public:
    Combat(Spirit spirit1, Spirit spirit2);
    void start() noexcept;
    void update() noexcept;
    int getValue(const SkillEffect &effect, int index) noexcept;
    ~Combat() = default;
};
