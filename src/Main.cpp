#include "database.h"
#include "user.h"
#include "utils.h"
#include "spirit.h"
#include <memory>
using namespace std;
int main()
{
    unique_ptr<Spirit> spirit = make_unique<Primeape>();
    cout << spirit.get()->format();
}