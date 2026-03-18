#pragma once

#include <drogon/HttpAppFramework.h>

using namespace drogon;

class Database
{
public:

    // Get default DB client
    static orm::DbClientPtr getClient();

    // Health check
    static bool isHealthy();
};