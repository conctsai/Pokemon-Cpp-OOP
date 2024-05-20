#include "database.hpp"
#include "user.hpp"
#include "utils.hpp"
#include "spirit.hpp"
#include <memory>
using namespace std;
int main()
{
    unique_ptr<Spirit> spirit = make_unique<Primeape>();
    cout << spirit.get()->format() << endl;
}