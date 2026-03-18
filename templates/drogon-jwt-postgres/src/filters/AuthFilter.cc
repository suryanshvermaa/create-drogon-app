/**
 *
 *  AuthFilter.cc
 *
 */

#include "AuthFilter.h"
#include "../utils/token.hpp"
#include"../utils/response.hpp"

using namespace drogon;

void AuthFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    const auto bearerToken = req->getHeader("Authorization");
    static const std::string tokenPrefix = "Bearer ";

    if (bearerToken.size() <= tokenPrefix.size() || bearerToken.rfind(tokenPrefix, 0) != 0)
    {
        fcb(Response::error(k401Unauthorized, "Unauthorized: Missing or invalid token"));
        return;
    }

    const std::string token = bearerToken.substr(tokenPrefix.size());
    data decodedData{};
    try
    {
        decodedData = Auth::decodeAndverifyToken(token);
    }
    catch (const std::exception &)
    {
        fcb(Response::error(k401Unauthorized, "Unauthorized: Invalid token"));
        return;
    }

    if (decodedData.userId>0)
    {
        req->setParameter("userId",std::to_string(decodedData.userId));
        req->setParameter("role",decodedData.role);
        fccb();
        return;
    }
    //Check failed
    fcb(Response::error(k401Unauthorized, "Unauthorized: Invalid token"));
}
