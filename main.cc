
#include <drogon/drogon.h>
#include "msg_controller.h"
#include "user_controller.h"
#include <drogon/WebSocketController.h>
using namespace drogon;
std::unordered_map<std::string, WebSocketConnectionPtr> clientTable;
int main() {
    drogon::app().addListener("0.0.0.0", 8081);
    std::cout << "ready" << std::endl;
    drogon::app().registerHandler("/api/signup", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        Handle(req, std::move(callback),registerUser);
    });
    drogon::app().registerHandler("/api/login", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        Handle(req, std::move(callback),loginUser);
    });
    drogon::app().registerHandler("/api/chat", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        chat(req, std::move(callback));
    });
    drogon::app().registerHandler("/api/check", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        check(req, std::move(callback));
    });
    drogon::app().registerHandler("/api/nfmgr", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        request_processing(req, std::move(callback));
    });
    drogon::app().registerHandler("/api/newfriends", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        friend_request(req, std::move(callback));
    });
      drogon::app().registerHandler("/api/info", [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        info(req, std::move(callback));
    });
    drogon::app().run();
    return 0;
}

