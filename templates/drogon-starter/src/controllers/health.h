#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class health : public drogon::HttpController<health>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(health::healthController, "", Get);

    METHOD_LIST_END
    void healthController(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
