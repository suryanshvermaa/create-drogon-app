#pragma once
#include <drogon/HttpAppFramework.h>

using namespace drogon;

class Response
{
public:

    static HttpResponsePtr success(
        const drogon::HttpStatusCode statusCode,
        const std::string& message = "success",
        const Json::Value& data=Json::nullValue)
    {
        Json::Value res;

        res["success"] = true;
        res["message"] = message;
        if(data!=Json::nullValue) res["data"]=data;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(statusCode);
        return resp;
    }

    static HttpResponsePtr error(
        const drogon::HttpStatusCode statusCode,
        const std::string& message)
    {
        Json::Value res;

        res["success"] = false;
        res["message"] = message;
        Json::Value err;
        auto resp=HttpResponse::newHttpJsonResponse(res);
        resp->setStatusCode(statusCode);
        return resp;
    }
};