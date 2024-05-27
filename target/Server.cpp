#include "hv/HttpServer.h"
#include <map>
#include "Platform/Platform.hpp"
#include "Utils/Json.hpp"
#include <memory>

int main()
{
    std::map<int, std::unique_ptr<Platform>> platforms;

    HttpService router;
    router.GET("/create_session", [&](const HttpContextPtr &ctx)
               {
                   int id = platforms.size();
                   platforms[id] = std::make_unique<Platform>();
                   hv::Json resp;
                   resp["session_id"] = id;
                   return ctx->send(resp.dump()); });

    router.POST("/login", [&](const HttpContextPtr &ctx)
                {
        hv::Json req = hv::Json::parse(ctx->body());
        hv::Json resp;
        std::string username = req["username"];
        std::string password = req["password"];
        int id = req["session_id"];
        if (platforms.find(id) == platforms.end())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Invalid session id";
            return ctx->send(resp.dump());
        }
        else
        {
            if (platforms[id]->login(username, password))
            {
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                resp["msg"] = "Login success";
                return ctx->send(resp.dump());
            }
            else
            {
                ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                resp["msg"] = "Login failed";
                return ctx->send(resp.dump());
            }
        } });

    router.POST("/register", [&](const HttpContextPtr &ctx)
                {
        hv::Json req = hv::Json::parse(ctx->body());
        hv::Json resp;
        std::string username = req["username"];
        std::string password = req["password"];
        int id = req["session_id"];
        if (platforms.find(id) == platforms.end())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Invalid session id";
            return ctx->send(resp.dump());
        }
        else
        {
            if (platforms[id]->registerUser(username, password))
            {
                platforms[id]->init();
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                resp["msg"] = "Register success";
                return ctx->send(resp.dump());
            }
            else
            {
                ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                resp["msg"] = "Register failed";
                return ctx->send(resp.dump());
            }
        } });
    // router.GET("/get_spirit_info", [&](HttpRequest *req, HttpResponse *resp)
    //            {
    //                int id = req->query["session_id"].get<int>();
    //                if (platforms.find(id) == platforms.end())
    //                {
    //                    resp->json["error"] = "Invalid session id";
    //                    return 404;
    //                }
    //                resp->json["spirit_info"] = platforms[id]->getSpiritInfo();
    //                return 200; });
    http_server_t server;
    server.port = 8080;
    server.service = &router;
    http_server_run(&server);
    return 0;
}