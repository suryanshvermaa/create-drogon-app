#include "health.h"
#include"../utils/response.hpp"
#include<json/json.h>
#include"../services/S3Service.h"

void health::healthController(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    try
    {
        callback(Response::success(k200OK,"heathy"));
    }
    catch(const std::exception& e)
    {
        LOG_ERROR << e.what();
        callback(Response::error(k400BadRequest,e.what()));
    }
    
}