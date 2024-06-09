#include "Platform/Combat.hpp"

Combat::Combat(Spirit spirit1, Spirit spirit2)
{
    this->spirit1 = std::make_unique<Spirit>(spirit1);
    this->spirit2 = std::make_unique<Spirit>(spirit2);
    this->spirit1SkillEffects.push_back(spirit1.getBasicSkill().getEffects());
    this->spirit1SkillEffects.push_back(spirit1.getSpecialSkill().getEffects());
    this->spirit1SkillEffects.push_back(spirit1.getUltimateSkill().getEffects());
    this->spirit2SkillEffects.push_back(spirit2.getBasicSkill().getEffects());
    this->spirit2SkillEffects.push_back(spirit2.getSpecialSkill().getEffects());
    this->spirit2SkillEffects.push_back(spirit2.getUltimateSkill().getEffects());
}

void Combat::start() noexcept
{
    result["fighter"].push_back(spirit1->getPetName());
    result["fighter"].push_back(spirit2->getPetName());
    while (spirit1->getHp() > 0 && spirit2->getHp() > 0)
    {
        tmp.clear();
        int speedSum = spirit1->getSpeed() + spirit2->getSpeed();
        int rand = utils::get_random_int(1, speedSum);
        if (rand <= spirit1->getSpeed())
        {
            int skillIndex = utils::get_random_int(0, 2);
            if (skillIndex == 0)
            {
                tmp["attack"] = spirit1->getPetName() + " 此轮攻击！，发动技能 " + spirit1->getBasicSkill().getName();
            }
            else if (skillIndex == 1)
            {
                tmp["attack"] = spirit1->getPetName() + " 此轮攻击！，发动技能 " + spirit1->getSpecialSkill().getName();
            }
            else
            {
                tmp["attack"] = spirit1->getPetName() + " 此轮攻击！，发动技能 " + spirit1->getUltimateSkill().getName();
            }
            for (auto &effect : spirit1SkillEffects[skillIndex])
            {
                skillQueue1.push(toFixValue(Goal::SELF, effect));
            }
        }
        else
        {
            int skillIndex = utils::get_random_int(0, 2);
            if (skillIndex == 0)
            {
                tmp["attack"] = spirit2->getPetName() + " 此轮攻击！，发动技能 " + spirit2->getBasicSkill().getName();
            }
            else if (skillIndex == 1)
            {
                tmp["attack"] = spirit2->getPetName() + " 此轮攻击！，发动技能 " + spirit2->getSpecialSkill().getName();
            }
            else
            {
                tmp["attack"] = spirit2->getPetName() + " 此轮攻击！，发动技能 " + spirit2->getUltimateSkill().getName();
            }
            for (auto &effect : spirit2SkillEffects[skillIndex])
            {
                skillQueue2.push(toFixValue(Goal::ENEMY, effect));
            }
        }
        update();
        tmp["property"].push_back(spirit1->toJson()["property"]);
        tmp["property"].push_back(spirit2->toJson()["property"]);
        result["round"].push_back(tmp);
    }

    if (spirit1->getHp() <= 0)
    {
        result["winner"] = 1;
    }
    else
    {
        result["winner"] = 0;
    }
}

void Combat::update() noexcept
{
    std::vector<SkillEffect> tempQueue;
    while (!skillQueue1.empty() && skillQueue1.top().activationTime == 0)
    {
        SkillEffect s = skillQueue1.top();
        skillQueue1.pop();
        handleEffect(Goal::SELF, s.source, s.target, s.description);
        if (s.duration != 0)
        {
            s.duration--;
            s.activationTime++;
            skillQueue1.push(s);
        }
    } // 处理技能队列1
    while (!skillQueue1.empty())
    {
        tempQueue.push_back(skillQueue1.top());
        skillQueue1.pop();
    }
    for (auto &s : tempQueue)
    {
        s.activationTime--;
    }
    for (const auto &s : tempQueue)
    {
        skillQueue1.push(s);
    }
    tempQueue.clear();

    while (!skillQueue2.empty() && skillQueue2.top().activationTime == 0)
    {
        SkillEffect s = skillQueue2.top();
        skillQueue2.pop();
        handleEffect(Goal::ENEMY, s.source, s.target, s.description);
        if (s.duration != 0)
        {
            s.duration--;
            s.activationTime++;
            skillQueue2.push(s);
        }
    } // 处理技能队列2
    while (!skillQueue2.empty())
    {
        tempQueue.push_back(skillQueue2.top());
        skillQueue2.pop();
    }
    for (auto &s : tempQueue)
    {
        s.activationTime--;
    }
    for (const auto &s : tempQueue)
    {
        skillQueue2.push(s);
    }
    tempQueue.clear();
}

int Combat::getValue(Goal s, Goal t, Type index) const noexcept
{
    switch ((s + t) % 2)
    {
    case 0:
        switch (index)
        {
        case Type::HP:
            return spirit1->getHp();
            break;
        case Type::ATTACKPOWER:
            return spirit1->getAttackPower();
            break;
        case Type::DEFENSEPOWER:
            return spirit1->getDefensePower();
            break;
        case Type::SPEED:
            return spirit1->getSpeed();
            break;
        default:
            exit(-1);
        }
        break;
    case 1:
        switch (index)
        {
        case Type::HP:
            return spirit2->getHp();
            break;
        case Type::ATTACKPOWER:
            return spirit2->getAttackPower();
            break;
        case Type::DEFENSEPOWER:
            return spirit2->getDefensePower();
            break;
        case Type::SPEED:
            return spirit2->getSpeed();
            break;
        default:
            exit(-1);
        }
        break;
    }
    exit(-1);
}

int Combat::getOldValue(Goal s, Goal t, Type index) const noexcept
{
    switch ((s + t) % 2)
    {
    case 0:
        switch (index)
        {
        case Type::HP:
            return spirit1->getHpOld();
            break;
        case Type::ATTACKPOWER:
            return spirit1->getAttackPowerOld();
            break;
        case Type::DEFENSEPOWER:
            return spirit1->getDefensePowerOld();
            break;
        case Type::SPEED:
            return spirit1->getSpeedOld();
            break;
        default:
            exit(-1);
        }
        break;
    case 1:
        switch (index)
        {
        case Type::HP:
            return spirit2->getHpOld();
            break;
        case Type::ATTACKPOWER:
            return spirit2->getAttackPowerOld();
            break;
        case Type::DEFENSEPOWER:
            return spirit2->getDefensePowerOld();
            break;
        case Type::SPEED:
            return spirit2->getSpeedOld();
            break;
        default:
            exit(-1);
        }
        break;
    }
    exit(-1);
}

void Combat::setValue(Goal s, Goal t, Type index, int value) noexcept
{
    switch ((s + t) % 2)
    {
    case 0:
        switch (index)
        {
        case Type::HP:
            spirit1->setHp(value);
            break;
        case Type::ATTACKPOWER:
            spirit1->setAttackPower(value);
            break;
        case Type::DEFENSEPOWER:
            spirit1->setDefensePower(value);
            break;
        case Type::SPEED:
            spirit1->setSpeed(value);
            break;
        default:
            exit(-1);
        }
        break;
    case 1:
        switch (index)
        {
        case Type::HP:
            spirit2->setHp(value);
            break;
        case Type::ATTACKPOWER:
            spirit2->setAttackPower(value);
            break;
        case Type::DEFENSEPOWER:
            spirit2->setDefensePower(value);
            break;
        case Type::SPEED:
            spirit2->setSpeed(value);
            break;
        default:
            exit(-1);
        }
        break;
    }
}

void Combat::handleEffect(Goal now, Source s, Target t, std::string des) noexcept
{
    int value = 0;
    if (s.type == Type::FIX_VALUE)
    {
        value = s.value;
    }
    else
    {
        exit(-1);
    }

    int rd = utils::get_random_int(1, 10);
    if (rd == 1)
    {
        // 未命中
        tmp["result"].push_back(GET_PET_NAME(now) + " 的 " + des + " 技能未命中！，" + GET_PET_NAME((now + t.goal) % 2) + " 未受到任何影响。");
    }
    else if (rd == 2)
    {
        // 暴击
        setValue(now, t.goal, t.type, getValue(now, t.goal, t.type) + value * 1.5);
        tmp["result"].push_back(GET_PET_NAME((now + t.goal) % 2) + " 受到了 " + GET_PET_NAME(now) + " 的 " + des + " 技能的影响，" + GET_TYPE_STRING(t.type) + " 由 " + std::to_string(getOldValue(now, t.goal, t.type)) + " 变为 " + std::to_string(getValue(now, t.goal, t.type)) + "，暴击！");
    }
    else
    {
        // 正常
        setValue(now, t.goal, t.type, getValue(now, t.goal, t.type) + value);
        tmp["result"].push_back(GET_PET_NAME((now + t.goal) % 2) + " 受到了 " + GET_PET_NAME(now) + " 的 " + des + " 技能的影响，" + GET_TYPE_STRING(t.type) + " 由 " + std::to_string(getOldValue(now, t.goal, t.type)) + " 变为 " + std::to_string(getValue(now, t.goal, t.type)));
    }
}

SkillEffect Combat::toFixValue(Goal g, SkillEffect se) noexcept
{
    if (se.source.type == Type::FIX_VALUE)
    {
        return se;
    }
    int value = getValue(g, se.source.goal, se.source.type) * se.source.value / 100;
    se.source.type = Type::FIX_VALUE;
    se.source.value = value;
    return se;
}