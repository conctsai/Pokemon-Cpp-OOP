#include "Platform/Platform.hpp"

using namespace std;
using namespace nlohmann;
int main()
{
    unique_ptr<Spirit> s = make_unique<Primeape>(std::string("czz"));
    cout << s->toJson().dump(4) << endl;
    s->addExp(100);
    cout << s->toJson().dump(4) << endl;
}