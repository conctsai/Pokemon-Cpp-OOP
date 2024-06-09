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

    ~ClientHttpDriver() = default;
};