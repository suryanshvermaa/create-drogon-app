#include<jwt-cpp/traits/open-source-parsers-jsoncpp/defaults.h>
#include"./token.hpp"
#include"crypt.h"
#include<random>
#include<sstream>
#include<iomanip>


std::string Auth::createToken(const int userId,const std::string &role){
    std::string token=jwt::create()
    .set_issuer("suryansh")
    .set_type("JWS")
    .set_expires_at(std::chrono::system_clock::now()+std::chrono::hours{24})
    .set_payload_claim("userId",jwt::claim(std::to_string(userId)))
    .set_payload_claim("role",jwt::claim(role))
    .sign(jwt::algorithm::hs256{std::getenv("JWT_SECRET")});
    
    return token;
}

data Auth::decodeAndverifyToken(const std::string &token){
    try
    {
        auto decodedToken=jwt::decode(token);
        auto verifier = jwt::verify()
        .with_issuer("suryansh")
        .with_type("JWS")
        .allow_algorithm(jwt::algorithm::hs256{std::getenv("JWT_SECRET")});

        verifier.verify(decodedToken);
        const std::string role=decodedToken.get_payload_claim("role").as_string();
        const std::string userId=decodedToken.get_payload_claim("userId").as_string();
        return {std::stoi(userId),role};
    }
    catch(const std::exception& e)
    {
        return {0,""};
    }
}

std::string generateSalt(int cost) {
    static const char table[] =
        "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 63);

    std::ostringstream ss;
    ss << "$2b$"
       << std::setw(2) << std::setfill('0') << cost
       << "$";

    for (int i = 0; i < 22; ++i)
        ss << table[dist(rd)];

    return ss.str();
}

std::string Auth::getHashPassword(const std::string &password){
    std::string salt = generateSalt(6);

    char* hash = crypt(password.c_str(), salt.c_str());
    if (!hash)
        throw std::runtime_error("Hashing failed");

    return std::string(hash);
}

bool Auth::comparePassword(const std::string &password, const std::string &storedHash){
    char* hash = crypt(password.c_str(), storedHash.c_str());
    if (!hash) return false;

    return std::strcmp(hash, storedHash.c_str()) == 0;
}