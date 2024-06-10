#include "Utils/SpiritUtils.hpp"
#include "Platform/Combat.hpp"
#include "Spirit/Spirit.hpp"

int main()
{
    std::unique_ptr<Spirit> spirit = SpiritUtils::getSpirit(SpiritUtils::getRandomSpirits(1));
    std::cout << spirit->toJson().dump(4);
    getchar();
    spirit->addExp(100);
    std::cout << spirit->toJson().dump(4);

    getchar();
    std::unique_ptr<Spirit> spirit2 = SpiritUtils::getSpirit(SpiritUtils::getRandomSpirits(1));
    std::cout << spirit2->toJson().dump(4);
    getchar();
    spirit2->addExp(100);
    std::cout << spirit2->toJson().dump(4);
    getchar();

    Combat combat(*spirit, *spirit2);
    combat.start();
    std::cout << combat.getResult().dump(4);
    return 0;
}