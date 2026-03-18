#include<drogon/HttpAppFramework.h>
#include <aws/core/Aws.h>
#include"./utils/dotenv.hpp"
#include"./config/database.h"
using namespace drogon;

int main(){
    Aws::SDKOptions awsOptions;
    Aws::InitAPI(awsOptions);

    Dotenv::load();
    const char* portEnv=std::getenv("PORT");
    app().loadConfigFile("./config/config.json");
    int port=3000;
    if (portEnv && *portEnv)
    {
        try
        {
            port = std::stoi(std::string(portEnv));
        }
        catch (const std::exception &e)
        {
            std::cerr << "Invalid PORT='" << portEnv << "' (" << e.what() << "); using " << port << "\n";
        }
    }
    else
    {
        std::cerr << "PORT not set (or .env missing); using " << port << "\n";
    }
    // CORS support
    app().registerPreRoutingAdvice([](
        const HttpRequestPtr &req, 
        std::function<void(const HttpResponsePtr &)> &&stop,
        std::function<void()> &&pass) {
        // Handle preflight OPTIONS requests
        if (req->method() == Options) {
            auto resp = HttpResponse::newHttpResponse();
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Methods", "*");
            resp->addHeader("Access-Control-Allow-Headers", "*, Authorization");
            resp->addHeader("Access-Control-Max-Age", std::to_string(86400));
            stop(resp); // Send response and stop further processing
            return;
        }
        pass(); // Continue processing for non-OPTIONS requests
    });

    // Register post-handling advice to add CORS headers to all responses
    app().registerPostHandlingAdvice([](const HttpRequestPtr &req, const HttpResponsePtr &resp) {
        resp->addHeader("Access-Control-Allow-Origin", "*");
    });
    auto threads = std::thread::hardware_concurrency();
    app().setThreadNum(threads);
    app().addListener("0.0.0.0",port);
    LOG_INFO << "=================================";
    LOG_INFO << "Starting Drogon Server";
    LOG_INFO << "Threads: " << threads;
    LOG_INFO << "Port: "<<port;
    LOG_INFO << "=================================";
    app().registerBeginningAdvice([]() {
        if (Database::isHealthy())
        {
            LOG_INFO << "Database connected successfully";
        }
        else
        {
            LOG_ERROR << "Database connection failed";
        }
    });
    app().run();

    Aws::ShutdownAPI(awsOptions);
    return 0;
}