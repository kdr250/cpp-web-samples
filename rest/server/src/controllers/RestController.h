#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class RestController : public drogon::HttpSimpleController<RestController>
{
public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req,
                                std::function<void(const HttpResponsePtr&)>&& callback) override;

    PATH_LIST_BEGIN
    PATH_ADD("/test", Get);
    PATH_LIST_END
};
