#pragma once
#include <stdexcept>
#include <string>
#include<drogon/HttpResponse.h>


using namespace drogon;

class AppError : public std::runtime_error {
public:
    drogon::HttpStatusCode statusCode;  

    explicit AppError(const std::string& message,
        drogon::HttpStatusCode statusCode = k500InternalServerError)
        : std::runtime_error(message), statusCode(statusCode) {}
};