#include "database.hpp"
#include "user.hpp"
#include "utils.hpp"
#include "spirit.hpp"
#include <memory>
#include "json.hpp"
using namespace std;
int main()
{
    unique_ptr<Spirit> spirit = make_unique<Primeape>();
    auto j = nlohmann::json::parse(spirit.get()->format());
    cout << j.dump() << endl;
}