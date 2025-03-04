#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api
{
    namespace v1
    {
        class Test : public drogon::HttpController<Test>
        {
        public:
            METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(Test::Index, "", Get);  //path is /api/v1/Test
            METHOD_LIST_END

            // your declaration of processing function maybe like this:
            void Index(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback) const;
        };
    }  // namespace v1
}  // namespace api
