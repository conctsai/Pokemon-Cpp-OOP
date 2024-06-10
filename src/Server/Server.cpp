#include "Server/Server.hpp"

Server::Server(int port)
{
    router.GET("/create_session", [&](const HttpContextPtr &ctx)
               {
                   mtx.lock();
                   int id = session_id++;
                   platforms[id] = std::make_unique<Platform>();
                   hv::Json resp;
                   resp["session_id"] = id;
                   mtx.unlock();
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
            // 判断用户是否已在其他客户端登录
            for (const auto &pair : platforms)
            {
                if (pair.second->getUserInterface().username == username)
                {
                    ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                    resp["msg"] = "User already logged in";
                    return ctx->send(resp.dump());
                }
            }

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

    router.GET("/logout", [&](const HttpContextPtr &ctx)
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
                platforms[id]->logout();
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                resp["msg"] = "Logout success";
            }
        }
        return ctx->send(resp.dump()); });

    router.POST("/exit", [&](const HttpContextPtr &ctx)
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
            platforms.erase(id);
            ctx->setStatus(http_status::HTTP_STATUS_OK);
            resp["msg"] = "Exit success";
        }
        return ctx->send(resp.dump()); });

    router.GET("/spirits/get", [&](const HttpContextPtr &ctx)
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

    router.POST("/spirits/add", [&](const HttpContextPtr &ctx)
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
                if (req["random"] == true) {
                    platforms[id]->addSpirit(SpiritUtils::getRandomSpirits(req["random_level"]).dump());
                } else {
                    platforms[id]->addSpirit(req["spirit_json"].dump());
                }
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                resp["msg"] = "Add success";
            }
        }
        return ctx->send(resp.dump()); });

    router.Delete("/spirits/delete", [&](const HttpContextPtr &ctx)
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
                if (platforms[id]->deleteSpirit(req["spirit_id"]))
                {
                    ctx->setStatus(http_status::HTTP_STATUS_OK);
                    resp["msg"] = "Delete success";
                }
                else
                {
                    ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                    resp["msg"] = "Delete failed";
                }
            }
        }
        return ctx->send(resp.dump()); });

    router.POST("/spirits/rename", [&](const HttpContextPtr &ctx)
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
                if (platforms[id]->renameSpirit(req["spirit_id"], req["new_name"]))
                {
                    ctx->setStatus(http_status::HTTP_STATUS_OK);
                    resp["msg"] = "Rename success";
                }
                else
                {
                    ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                    resp["msg"] = "Rename failed";
                }
            }
        }
        return ctx->send(resp.dump()); });

    router.POST("/spirits/level_up", [&](const HttpContextPtr &ctx)
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
                if (platforms[id]->updateSpirit(req["spirit_id"], req["exp"]))
                {
                    ctx->setStatus(http_status::HTTP_STATUS_OK);
                    resp["msg"] = "Level up success";
                }
                else
                {
                    ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                    resp["msg"] = "Level up failed";
                }
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

    router.GET("/combat", [&](const HttpContextPtr &ctx)
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
                Spirit spirit1 = *SpiritUtils::getSpirit(req["spirits"][0]).get();
                Spirit spirit2 = *SpiritUtils::getSpirit(req["spirits"][1]).get();
                std::unique_ptr<Combat> combat = std::make_unique<Combat>(spirit1, spirit2);
                combat->start();
                resp = combat->getResult();
                combat.reset();
            }
        }
        return ctx->send(resp.dump()); });

    router.GET("/all_users", [&](const HttpContextPtr &ctx)
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
                hv::Json userInfo;
                std::vector<UserInterface> ui = USERDRIVER.getAllUsers();
                std::vector<SpiritInterface> si;
                bool online = false;
                for (const auto &user : ui)
                {
                    online = false;
                    si.clear();
                    userInfo.clear();
                    userInfo["username"] = user.username;
                    userInfo["id"] = user.id;
                    si = SPIRITDRIVER.getSpiritsByUserId(user.id);
                    for (const auto &spirit : si)
                    {
                        userInfo["spirits"].push_back(hv::Json::parse(spirit.spirit_json));
                    }
                    for (const auto &pair : platforms)
                    {
                        if (pair.second->getUserInterface().id == user.id)
                        {
                            online = true;
                            break;
                        }
                    }
                    userInfo["online"] = online;
                    resp.push_back(userInfo);
                }
            }
        }
        return ctx->send(resp.dump()); });

    router.GET("/get_win", [&](const HttpContextPtr &ctx)
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
                WinInterface w = WINDRIVER.getWinByUserId(platforms[id]->getUserInterface().id);
                if (w.total == 0) {
                    resp["win_rate"] = 0;
                } else {
                    resp["win_rate"] = (double)w.win / w.total * 100;
                }
            }
        }
        return ctx->send(resp.dump()); });

    router.POST("/update_win", [&](const HttpContextPtr &ctx)
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
                WinInterface w = WINDRIVER.getWinByUserId(platforms[id]->getUserInterface().id);
                if (req["win"] == true)
                {
                    WINDRIVER.updateWin(platforms[id]->getUserInterface().id, w.win + 1, w.total + 1);
                }
                else
                {
                    WINDRIVER.updateWin(platforms[id]->getUserInterface().id, w.win, w.total + 1);
                }
                resp["msg"] = "Update success";
            }
        }
        return ctx->send(resp.dump()); });

    router.POST("/join_match", [&](const HttpContextPtr &ctx)
                {
        hv::Json req = hv::Json::parse(ctx->body());
        hv::Json resp;
        match m;
        m.session_id = req["session_id"];
        if (platforms.find(m.session_id) == platforms.end())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Invalid session id";
        }
        if (!platforms[m.session_id]->getLoginStatus())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Not logged in";
        }
        else
        {
            m.spirit = hv::Json::parse(SPIRITDRIVER.getSpiritById(req["spirit_id"]).spirit_json);
            m.is_match = false;
            m.result = nullptr;
            matching_queue.push(m);
            ctx->setStatus(http_status::HTTP_STATUS_OK);
            resp["msg"] = "Join success";
        }
        return ctx->send(resp.dump()); });

    router.GET("/get_match", [&](const HttpContextPtr &ctx)
               {
        hv::Json req = hv::Json::parse(ctx->body());
        hv::Json resp;
        int id = req["session_id"];
        if (platforms.find(id) == platforms.end())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Invalid session id";
        }
        if (!platforms[id]->getLoginStatus())
        {
            ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
            resp["msg"] = "Not logged in";
        }
        else
        {
            if (matching_queue.size() >= 2 && matching_queue.front().session_id == id)
            {
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                match m = matching_queue.front();
                matching_queue.pop();
                Spirit spirit1 = *SpiritUtils::getSpirit(m.spirit).get();
                Spirit spirit2 = *SpiritUtils::getSpirit(matching_queue.front().spirit).get();
                Combat c(spirit1, spirit2);
                c.start();
                m.result = c.getResult();
                m.is_match = true;
                m.enemy_session_id = matching_queue.front().session_id;
                matching_queue.front().result = m.result;
                matching_queue.front().is_match = true;
                matching_queue.front().enemy_session_id = m.session_id;
                resp["enemy"] = platforms[m.enemy_session_id]->getUserInterface().username;
                resp["enemy_spirit"] = matching_queue.front().spirit;
                resp["result"] = m.result;
                matching_queue.front().spirit = m.spirit;
            }
            else if (matching_queue.front().session_id == id && matching_queue.front().is_match == true)
            {
                ctx->setStatus(http_status::HTTP_STATUS_OK);
                match m = matching_queue.front();
                matching_queue.pop();
                resp["enemy"] = platforms[m.enemy_session_id]->getUserInterface().username;
                resp["enemy_spirit"] = m.spirit;
                resp["result"] = m.result;
            }
            else
            {
                ctx->setStatus(http_status::HTTP_STATUS_NOT_FOUND);
                resp["msg"] = "No match";
            }
        }
        return ctx->send(resp.dump()); });

    server.port = port;
    server.service = &router;
}

void Server::run()
{
    server.worker_threads = 4;
    http_server_run(&server);
}