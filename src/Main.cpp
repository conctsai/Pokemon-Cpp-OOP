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
    unique_ptr<Primeape> p1 = make_unique<Primeape>(std::string("czz"));
    unique_ptr<Primeape> p2 = make_unique<Primeape>(std::string("wyf"));
    Combat combat((Spirit(*p1)), (Spirit(*p2)));
    combat.start();
}