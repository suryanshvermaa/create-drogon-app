#include "database.h"

using namespace drogon;
using namespace drogon::orm;

DbClientPtr Database::getClient()
{
    return app().getDbClient();
}

bool Database::isHealthy()
{
    try
    {
        auto db = getClient();
        auto result = db->execSqlSync("SELECT 1");
        return result.size() > 0;
    }
    catch(...)
    {
        return false;
    }
}