#include "Platform/combat.hpp"

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
    std::cout << "精灵1：" << spirit1->getName() << " VS 精灵2：" << spirit2->getName() << std::endl;
    std::cout << "战斗开始！" << std::endl;
    getchar(); // 暂停
    while (spirit1->getHp() > 0 && spirit2->getHp() > 0)
    {
        getchar();
        int speedSum = spirit1->getSpeed() + spirit2->getSpeed();
        int rand = utils::get_random_int(1, speedSum);
        if (rand <= spirit1->getSpeed())
        {
            std::cout << spirit1->getName() << " 攻击！" << std::endl;
            int skillIndex = utils::get_random_int(0, 2);
            std::cout << spirit1->getName() << "发动技能" << skillIndex << std::endl;
            for (auto &effect : spirit1SkillEffects[skillIndex])
            {
                skillQueue1.push(effect);
            }
        }
        else
        {
            std::cout << spirit2->getName() << " 攻击！" << std::endl;
            int skillIndex = utils::get_random_int(0, 2);
            std::cout << spirit2->getName() << "发动技能" << skillIndex << std::endl;
            for (auto &effect : spirit2SkillEffects[skillIndex])
            {
                skillQueue2.push(effect);
            }
        }
        update();
    }
}

void Combat::update() noexcept
{
    while (!skillQueue1.empty() || !skillQueue2.empty())
    {
        if (!skillQueue1.empty() && skillQueue1.front().activationTime == 0)
        {
            auto effect = skillQueue1.front();
            if (skillQueue1.front().duration == 0)
            {
                skillQueue1.pop();
            }
            else
            {
                skillQueue1.front().duration--;
            }

            switch (effect.target.goal)
            {
            case Goal::ENEMY:
                switch (effect.target.type)
                {
                case Type::HP:
                    spirit2->setHp(spirit2->getHp() + getValue(effect, 1));
                    std::cout << spirit2->getName() << "受到了" << getValue(effect, 1) << "点伤害" << std::endl;
                    break;
                case Type::SPEED:
                    spirit2->setSpeed(spirit2->getSpeed() + getValue(effect, 1));
                    std::cout << spirit2->getName() << "速度降低了" << getValue(effect, 1) << std::endl;
                    break;
                case Type::ATTACKPOWER:
                    spirit2->setAttackPower(spirit2->getAttackPower() + getValue(effect, 1));
                    std::cout << spirit2->getName() << "攻击力降低了" << getValue(effect, 1) << std::endl;
                    break;
                case Type::DEFENSEPOWER:
                    spirit2->setDefensePower(spirit2->getDefensePower() + getValue(effect, 1));
                    std::cout << spirit2->getName() << "防御力降低了" << getValue(effect, 1) << std::endl;
                    break;
                }
                break;
            case Goal::SELF:
                switch (effect.target.type)
                {
                case Type::HP:
                    spirit1->setHp(spirit1->getHp() + getValue(effect, 1));
                    std::cout << spirit1->getName() << "回复了" << getValue(effect, 1) << "点血量" << std::endl;
                    break;
                case Type::SPEED:
                    spirit1->setSpeed(spirit1->getSpeed() + getValue(effect, 1));
                    std::cout << spirit1->getName() << "速度提升了" << getValue(effect, 1) << std::endl;
                    break;
                case Type::ATTACKPOWER:
                    spirit1->setAttackPower(spirit1->getAttackPower() + getValue(effect, 1));
                    std::cout << spirit1->getName() << "攻击力提升了" << getValue(effect, 1) << std::endl;
                    break;
                case Type::DEFENSEPOWER:
                    spirit1->setDefensePower(spirit1->getDefensePower() + getValue(effect, 1));
                    std::cout << spirit1->getName() << "防御力提升了" << getValue(effect, 1) << std::endl;
                    break;
                }
                break;
            }
        }
        if (!skillQueue2.empty() && skillQueue2.front().activationTime == 0)
        {
            auto effect = skillQueue2.front();
            if (skillQueue2.front().duration == 0)
            {
                skillQueue2.pop();
            }
            else
            {
                skillQueue2.front().duration--;
            }
            switch (effect.target.goal)
            {
            case Goal::ENEMY:
                switch (effect.target.type)
                {
                case Type::HP:
                    spirit1->setHp(spirit1->getHp() + getValue(effect, 2));
                    std::cout << spirit1->getName() << "受到了" << getValue(effect, 2) << "点伤害" << std::endl;
                    break;
                case Type::SPEED:
                    spirit1->setSpeed(spirit1->getSpeed() + getValue(effect, 2));
                    std::cout << spirit1->getName() << "速度降低了" << getValue(effect, 2) << std::endl;
                    break;
                case Type::ATTACKPOWER:
                    spirit1->setAttackPower(spirit1->getAttackPower() + getValue(effect, 2));
                    std::cout << spirit1->getName() << "攻击力降低了" << getValue(effect, 2) << std::endl;
                    break;
                case Type::DEFENSEPOWER:
                    spirit1->setDefensePower(spirit1->getDefensePower() + getValue(effect, 2));
                    std::cout << spirit1->getName() << "防御力降低了" << getValue(effect, 2) << std::endl;
                    break;
                }
                break;
            case Goal::SELF:
                switch (effect.target.type)
                {
                case Type::HP:
                    spirit2->setHp(spirit2->getHp() + getValue(effect, 2));
                    std::cout << spirit2->getName() << "回复了" << getValue(effect, 2) << "点血量" << std::endl;
                    break;
                case Type::SPEED:
                    spirit2->setSpeed(spirit2->getSpeed() + getValue(effect, 2));
                    std::cout << spirit2->getName() << "速度提升了" << getValue(effect, 2) << std::endl;
                    break;
                case Type::ATTACKPOWER:
                    spirit2->setAttackPower(spirit2->getAttackPower() + getValue(effect, 2));
                    std::cout << spirit2->getName() << "攻击力提升了" << getValue(effect, 2) << std::endl;
                    break;
                case Type::DEFENSEPOWER:
                    spirit2->setDefensePower(spirit2->getDefensePower() + getValue(effect, 2));
                    std::cout << spirit2->getName() << "防御力提升了" << getValue(effect, 2) << std::endl;
                    break;
                }
                break;
            }
        }
    }
}

int Combat::getValue(const SkillEffect &effect, int index) noexcept
{
    switch (effect.source.goal)
    {
    case Goal::ENEMY:
        if (index == 1)
        {
            switch (effect.source.type)
            {
            case Type::HP_PERCENT:
                return spirit2->getHp() * effect.source.value / 100;
                break;
            case Type::ATTACKPOWER_PERCENT:
                return spirit2->getAttackPower() * effect.source.value / 100;
                break;
            case Type::DEFENSEPOWER_PERCENT:
                return spirit2->getDefensePower() * effect.source.value / 100;
                break;
            case Type::SPEED_PERCENT:
                return spirit2->getSpeed() * effect.source.value / 100;
                break;
            case Type::FIX_VALUE:
                return effect.source.value;
                break;
            default:
                exit(-1);
            }
        }
        else if (index == 2)
        {
            switch (effect.source.type)
            {
            case Type::HP_PERCENT:
                return spirit1->getHp() * effect.source.value / 100;
                break;
            case Type::ATTACKPOWER_PERCENT:
                return spirit1->getAttackPower() * effect.source.value / 100;
                break;
            case Type::DEFENSEPOWER_PERCENT:
                return spirit1->getDefensePower() * effect.source.value / 100;
                break;
            case Type::SPEED_PERCENT:
                return spirit1->getSpeed() * effect.source.value / 100;
                break;
            case Type::FIX_VALUE:
                return effect.source.value;
                break;
            default:
                exit(-1);
            }
        }
        break;

    case Goal::SELF:
        if (index == 1)
        {
            switch (effect.source.type)
            {
            case Type::HP_PERCENT:
                return spirit1->getHp() * effect.source.value / 100;
                break;
            case Type::ATTACKPOWER_PERCENT:
                return spirit1->getAttackPower() * effect.source.value / 100;
                break;
            case Type::DEFENSEPOWER_PERCENT:
                return spirit1->getDefensePower() * effect.source.value / 100;
                break;
            case Type::SPEED_PERCENT:
                return spirit1->getSpeed() * effect.source.value / 100;
                break;
            case Type::FIX_VALUE:
                return effect.source.value;
                break;
            default:
                exit(-1);
            }
        }
        else if (index = 2)
        {
            switch (effect.source.type)
            {
            case Type::HP_PERCENT:
                return spirit2->getHp() * effect.source.value / 100;
                break;
            case Type::ATTACKPOWER_PERCENT:
                return spirit2->getAttackPower() * effect.source.value / 100;
                break;
            case Type::DEFENSEPOWER_PERCENT:
                return spirit2->getDefensePower() * effect.source.value / 100;
                break;
            case Type::SPEED_PERCENT:
                return spirit2->getSpeed() * effect.source.value / 100;
                break;
            case Type::FIX_VALUE:
                return effect.source.value;
                break;
            default:
                exit(-1);
            }
        }
        break;
    }
    exit(-1);
}