#include "Server/Server.hpp"

Server::Server(int port)
{
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
                platforms[id]->init();
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

    router.GET("/spirits", [&](const HttpContextPtr &ctx)
               {
        hv::Json req = hv::Json::parse(ctx->body());
        hv::Json resp;
        int id = req["session_id"];
        if (platforms.find(id) == platforms.end())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Invalid session id";
        } else {
            if (!platforms[id]->getLoginStatus()) {
                ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                resp["msg"] = "Not logged in";
            } else {
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                resp = platforms[id]->getSpirits();
            }
        }
        return ctx->send(resp.dump()); });

    router.GET("/random_spirits", [&](const HttpContextPtr &ctx)
               {
        hv::Json req = hv::Json::parse(ctx->body());
        hv::Json resp;
        int id = req["session_id"];
        if (platforms.find(id) == platforms.end())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Invalid session id";
        }
        else
        {
            if (!platforms[id]->getLoginStatus())
            {
                ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                resp["msg"] = "Not logged in";
            }
            else
            {
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                resp = SpiritUtils::getRandomSpirits(platforms[id]->getMaxLevel());
            }
        }
        return ctx->send(resp.dump()); });

    server.port = port;
    server.service = &router;
}

void Server::run()
{
    http_server_run(&server);
}