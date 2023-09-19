#include <drogon/drogon.h>
#include <json/json.h>
#include "mysql.h"
#include "jwt_controller.h"
#include "msg_controller.h"
using namespace drogon;
typedef std::string (*HandlerFunc)(const Json::Value&);
void Handle(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, HandlerFunc handler){
    auto body = req->getBody();
    Json::Value req_json,res_json;
    Json::Reader reader;
    std::string bodyStr(body);
    if (!reader.parse(bodyStr, req_json)) {
        callback(HttpResponse::newHttpResponse());
        return;
    }
    Json::FastWriter writer;
    std::string msg = handler(req_json);
    res_json["msg"] = msg;
    if (msg.find("Success")!= std::string::npos){
        res_json["token"] = jwtGen(req_json);
        res_json["username"] = req_json["username"].asString();
    }
    auto output = writer.write(res_json);
    auto res = HttpResponse::newHttpResponse();
    res->addHeader("Access-Control-Allow-Origin", "*");
    res->setBody(output);
    callback(res);
}
std::string registerUser(const Json::Value& req_json) {
    // std::cout<<"Receive Username : "<<req_json["username"].asString()<<std::endl;
    // std::cout<<"Receive Passwd: "<<req_json["password"].asString()<<std::endl;
    if (sql_check(req_json["username"].asString())){
        sql_add(req_json["username"].asString(), req_json["password"].asString(), req_json["avatar"].asInt());
        return "Sign up Success";
    }else
        return "User already exist";
}
std::string loginUser(const Json::Value& req_json) {
    if (sql_check(req_json["username"].asString(), req_json["password"].asString())){
        return "Login Success";
    }else
        return "Login Failed";
}
void avatar(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto res = HttpResponse::newHttpResponse();
    res->addHeader("Access-Control-Allow-Origin", "*");
    if (jwtVerify(req)) {
        std::string receiver = jwtDecrypt(req->getHeader("Authorization").substr(7));
        set_avatar(receiver, stoi(req->getParameter("avatar")));
        res->setBody("Success");
    } else {
        res->setBody("No Authorization");
    }
    callback(res);
}