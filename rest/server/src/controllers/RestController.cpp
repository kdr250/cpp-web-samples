#include "RestController.h"

void RestController::asyncHandleHttpRequest(const HttpRequestPtr& req,
                                            std::function<void(const HttpResponsePtr&)>&& callback)
{
    // write your application logic here
    auto response = HttpResponse::newHttpResponse();
    response->setBody("<p>Hello, World!</p>");
    response->setExpiredTime(0);
    callback(response);
}
