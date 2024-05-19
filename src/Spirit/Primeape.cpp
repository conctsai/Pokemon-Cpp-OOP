#include "spirit.h"

std::vector<SkillEffect> Primeape::basicAttackEffects()
{
    return std::vector<SkillEffect>{
        SkillEffect(Type::HP, -10, GOAL::ENEMY, 0, 0),
        // 减少对手10点HP，立即生效
    };
}

std::vector<SkillEffect> Primeape::specialAttackEffects()
{
    return std::vector<SkillEffect>{
        SkillEffect(Type::HP_PERCENT, -10, GOAL::ENEMY, 0, 2),
        SkillEffect(Type::SPEED, 10, GOAL::SELF, 0, 0),
        // 减少对手10%血量，立即生效，持续两回合
        // 提升自身速度10，立即生效
    };
}