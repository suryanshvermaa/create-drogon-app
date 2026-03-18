#pragma once

#include <aws/core/auth/AWSCredentials.h>
#include <aws/core/client/ClientConfiguration.h>
#include <string>
#include <cstdlib>

namespace AwsConfig
{

inline std::string getEnv(const std::string& key,
                          const std::string& defaultValue = "")
{
    const char* value = std::getenv(key.c_str());
    return value ? std::string(value) : defaultValue;
}

inline bool getEnvBool(const std::string& key,
                       bool defaultValue = false)
{
    auto value = getEnv(key);
    if (value == "true" || value == "1")
        return true;
    if (value == "false" || value == "0")
        return false;
    return defaultValue;
}

struct StorageConfig
{
    std::string endpoint;
    std::string region;
    std::string accessKey;
    std::string secretKey;
    std::string bucket;
    bool useSSL;
};

inline StorageConfig load()
{
    StorageConfig config;

    config.endpoint = getEnv("S3_ENDPOINT");
    config.region = getEnv("S3_REGION", "us-east-1");
    config.accessKey = getEnv("S3_ACCESS_KEY");
    config.secretKey = getEnv("S3_SECRET_KEY");
    config.bucket = getEnv("S3_BUCKET");
    config.useSSL = getEnvBool("S3_USE_SSL", true);
    return config;
}

inline Aws::Auth::AWSCredentials credentials()
{
    return Aws::Auth::AWSCredentials(
        getEnv("S3_ACCESS_KEY"),
        getEnv("S3_SECRET_KEY")
    );
}

inline Aws::Client::ClientConfiguration clientConfig()
{
    Aws::Client::ClientConfiguration config;

    config.region = getEnv("S3_REGION", "us-east-1");
    auto endpoint = getEnv("S3_ENDPOINT");
    if (!endpoint.empty())
    {
        const std::string httpPrefix = "http://";
        const std::string httpsPrefix = "https://";
        if (endpoint.rfind(httpPrefix, 0) == 0)
            endpoint = endpoint.substr(httpPrefix.size());
        else if (endpoint.rfind(httpsPrefix, 0) == 0)
            endpoint = endpoint.substr(httpsPrefix.size());

        config.endpointOverride = endpoint;
    }

    config.scheme = getEnvBool("S3_USE_SSL", true)
        ? Aws::Http::Scheme::HTTPS
        : Aws::Http::Scheme::HTTP;

    config.verifySSL = getEnvBool("S3_USE_SSL", true);

    return config;
}

}