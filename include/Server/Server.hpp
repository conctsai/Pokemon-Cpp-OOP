#include "hv/HttpServer.h"
#include <map>
#include "Platform/Platform.hpp"
#include <memory>

class Server
{
private:
    std::map<int, std::unique_ptr<Platform>> platforms;
    HttpService router;
    http_server_t server;

public:
    Server(int port);
    void run();
    ~Server() = default;
};