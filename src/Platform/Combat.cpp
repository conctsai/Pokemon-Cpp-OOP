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
    std::cout << "精灵1：" << spirit1->getPetName() << " VS 精灵2：" << spirit2->getPetName() << std::endl;
    std::cout << "按下Enter键战斗开始！" << std::endl;
    getchar(); // 暂停
    while (spirit1->getHp() > 0 && spirit2->getHp() > 0)
    {
        getchar();
        int speedSum = spirit1->getSpeed() + spirit2->getSpeed();
        int rand = utils::get_random_int(1, speedSum);
        if (rand <= spirit1->getSpeed())
        {
            std::cout << spirit1->getPetName() << " 此轮攻击！" << std::endl;
            int skillIndex = utils::get_random_int(0, 2);
            std::cout << spirit1->getPetName() << " 发动技能 ";
            if (skillIndex == 0)
            {
                std::cout << spirit1->getBasicSkill().getName() << std::endl;
            }
            else if (skillIndex == 1)
            {
                std::cout << spirit1->getSpecialSkill().getName() << std::endl;
            }
            else
            {
                std::cout << spirit1->getUltimateSkill().getName() << std::endl;
            }
            for (auto &effect : spirit1SkillEffects[skillIndex])
            {
                skillQueue1.push(effect);
            }
        }
        else
        {
            std::cout << spirit2->getPetName() << " 此轮攻击！" << std::endl;
            int skillIndex = utils::get_random_int(0, 2);
            std::cout << spirit2->getPetName() << " 发动技能 ";
            if (skillIndex == 0)
            {
                std::cout << spirit2->getBasicSkill().getName() << std::endl;
            }
            else if (skillIndex == 1)
            {
                std::cout << spirit2->getSpecialSkill().getName() << std::endl;
            }
            else
            {
                std::cout << spirit2->getUltimateSkill().getName() << std::endl;
            }
            for (auto &effect : spirit2SkillEffects[skillIndex])
            {
                skillQueue2.push(effect);
            }
        }
        update();
        std::cout << spirit1->getPetName() << "\n"
                  << spirit1->toJson()["property"].dump(4) << std::endl;
        std::cout << spirit2->getPetName() << "\n"
                  << spirit2->toJson()["property"].dump(4) << std::endl;
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
        value = getValue(now, s.goal, s.type) * s.value / 100;
    }

    setValue(now, t.goal, t.type, getValue(now, t.goal, t.type) + value);

    std::cout << GET_PET_NAME((now + t.goal) % 2) << " 受到了 " << GET_PET_NAME(now) << " 的 " << des << " 技能的影响，"
              << GET_TYPE_STRING(t.type) << " 由 " << getOldValue(now, t.goal, t.type) << " 变为 "
              << getValue(now, t.goal, t.type) << std::endl;
}