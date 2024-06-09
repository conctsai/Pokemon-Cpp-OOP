#include "Client/Client.hpp"
#include "Database/WinDriver.hpp"

int main()
{
    Client client("http://localhost:8080");
    client.run();
    return 0;
}
