#include "Client/Client.hpp"

int main()
{
    Client client("http://localhost:8080");
    client.run();
    return 0;
}
