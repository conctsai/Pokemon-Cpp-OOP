#include "hv/HttpServer.h"
#include "hv/EventLoop.h"
#include <map>
#include "Platform/Platform.hpp"
#include "Platform/Combat.hpp"
#include <memory>
#include <queue>
#include <iostream>
#include <mutex>

struct match
{
    int session_id;
    hv::Json spirit;
    bool is_match;
    hv::Json result;
    int enemy_session_id;
};

class Server
{
private:
    std::map<int, std::unique_ptr<Platform>> platforms;
    std::mutex mtx;
    HttpService router;
    http_server_t server;
    int session_id = 0;
    std::queue<match> matching_queue;

public:
    Server(int port);
    void run();
    ~Server() = default;
};