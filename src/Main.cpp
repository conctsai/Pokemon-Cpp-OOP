#include "database.hpp"
#include "user.hpp"
#include "utils.hpp"
#include "spirit.hpp"
#include <memory>
#include "json.hpp"
#include "combat.hpp"
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