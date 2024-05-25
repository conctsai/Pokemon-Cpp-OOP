#pragma once

#include "Spirit/Spirit.hpp"
#include "Utils/Utils.hpp"
#include <memory>
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include "Utils/Json.hpp"

#define GET_PET_NAME(x) ((x) == 0 ? spirit1->getPetName() : (x) == 1 ? spirit2->getPetName() \
                                                                     : "Invalid index")

class Combat
{
private:
    std::unique_ptr<Spirit> spirit1;
    std::unique_ptr<Spirit> spirit2;
    std::vector<std::vector<SkillEffect>> spirit1SkillEffects;
    std::vector<std::vector<SkillEffect>> spirit2SkillEffects;
    std::priority_queue<SkillEffect> skillQueue1;
    std::priority_queue<SkillEffect> skillQueue2;

public:
    Combat(Spirit spirit1, Spirit spirit2);
    void start() noexcept;
    void update() noexcept;
    int getValue(Goal s, Goal t, Type index) const noexcept;
    int getOldValue(Goal s, Goal t, Type index) const noexcept;
    void setValue(Goal s, Goal t, Type index, int value) noexcept;
    void handleEffect(Goal now, Source s, Target t, std::string des) noexcept;
    ~Combat() = default;
};
