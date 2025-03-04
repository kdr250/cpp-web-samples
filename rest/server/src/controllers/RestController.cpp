#include "RestController.h"

void api::v1::Test::Index(const HttpRequestPtr& req,
                          std::function<void(const HttpResponsePtr&)>&& callback) const
{
    // write your application logic here
    Json::Value result;
    result["message"] = "Hello, World!";
    auto response     = HttpResponse::newHttpJsonResponse(result);
    callback(response);
}
