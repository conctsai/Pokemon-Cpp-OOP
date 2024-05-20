#include "Database/Database.hpp"
#include "User/User.hpp"
#include "Utils/Utils.hpp"
#include "Spirit/Spirit.hpp"
#include <memory>
#include "Utils/Json.hpp"
#include "Platform/Combat.hpp"
using namespace std;
int main()
{
    unique_ptr<Spirit> spirit1 = make_unique<Primeape>(Primeape("火爆猴1"));
    unique_ptr<Spirit> spirit2 = make_unique<Primeape>(Primeape("火爆猴2"));
    getchar();
    Combat combat1(*spirit1, *spirit2);
    getchar();
    combat1.start();
}