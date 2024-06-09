#include <string>
#include <hv/requests.h>

class ClientHttpDriver
{
private:
    std::string url;

public:
    ClientHttpDriver(const std::string &url) { this->url = url; };
    int get_session_id()
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_GET;
        req->url = this->url + "/create_session";
        requests::Response resp = requests::request(req);
        return hv::Json::parse(resp->body)["session_id"];
    }

    bool login(const std::string &username, const std::string &password, int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/login";
        req->body = hv::Json({{"username", username}, {"password", password}, {"session_id", session_id}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    bool register_user(const std::string &username, const std::string &password, int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/register";
        req->body = hv::Json({{"username", username}, {"password", password}, {"session_id", session_id}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    bool exit(int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/exit";
        req->body = hv::Json({{"session_id", session_id}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    bool logout(int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_GET;
        req->url = this->url + "/logout";
        req->body = hv::Json({{"session_id", session_id}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    hv::Json get_spirits(int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_GET;
        req->url = this->url + "/spirits/get";
        req->body = hv::Json({{"session_id", session_id}}).dump();
        requests::Response resp = requests::request(req);
        return hv::Json::parse(resp->body);
    }

    hv::Json get_system_spirits(int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_GET;
        req->url = this->url + "/random_spirits";
        req->body = hv::Json({{"session_id", session_id}}).dump();
        requests::Response resp = requests::request(req);
        return hv::Json::parse(resp->body);
    }

    bool rename_spirit(int session_id, int spirit_id, const std::string &new_name)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/spirits/rename";
        req->body = hv::Json({{"session_id", session_id}, {"spirit_id", spirit_id}, {"new_name", new_name}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    hv::Json get_combat_result(int session_id, hv::Json spirit1, hv::Json spirit2)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_GET;
        req->url = this->url + "/combat";
        hv::Json body;
        body["session_id"] = session_id;
        body["spirits"].push_back(spirit1);
        body["spirits"].push_back(spirit2);
        req->body = body.dump();
        requests::Response resp = requests::request(req);
        return hv::Json::parse(resp->body);
    }

    bool level_up(int session_id, int spirit_id, int exp)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/spirits/level_up";
        req->body = hv::Json({{"session_id", session_id}, {"spirit_id", spirit_id}, {"exp", exp}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    bool add_spirit(int session_id, hv::Json spirit)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/spirits/add";
        req->body = hv::Json({{"session_id", session_id}, {"spirit_json", spirit}, {"random", false}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    bool add_random_spirit(int session_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_POST;
        req->url = this->url + "/spirits/add";
        req->body = hv::Json({{"session_id", session_id}, {"random", true}, {"random_level", 1}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }

    bool delete_spirit(int session_id, int spirit_id)
    {
        HttpRequestPtr req(new HttpRequest);
        req->method = HTTP_DELETE;
        req->url = this->url + "/spirits/delete";
        req->body = hv::Json({{"session_id", session_id}, {"spirit_id", spirit_id}}).dump();
        requests::Response resp = requests::request(req);
        return resp->status_code == 200;
    }
    ~ClientHttpDriver() = default;
};