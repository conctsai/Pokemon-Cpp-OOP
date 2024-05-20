#include "Database/database.hpp"
#include "User/user.hpp"
#include "Utils/utils.hpp"
#include "Spirit/spirit.hpp"
#include <memory>
#include "Utils/json.hpp"
#include "Platform/combat.hpp"
using namespace std;
int main()
{
    unique_ptr<Spirit> spirit1 = make_unique<Primeape>();
    unique_ptr<Spirit> spirit2 = make_unique<Primeape>();
    getchar();
    Combat combat1(*spirit1, *spirit2);
    getchar();
    combat1.start();
}