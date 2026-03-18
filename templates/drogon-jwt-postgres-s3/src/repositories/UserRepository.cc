#include"./UserRepository.h"
#include"../models/Users.h"
#include"../config/database.h"

using namespace drogon_model::drogon_jwt_postgres_s3;
using namespace drogon::orm;

int UserRepository::createUser(const user& u){
    try
    {
        Users user;
        user.setUsername(u.name);
        user.setEmail(u.email);
        user.setPassword(u.password);
        Mapper<Users> mapper(Database::getClient());
        mapper.insert(user);
        return user.getValueOfId();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
}

std::vector<user> UserRepository::getUsers(int page,int limit){
    try
    {
        std::vector<user> users;
        Mapper<Users> mapper(Database::getClient());
        auto dbUsers=mapper.limit(limit).offset((page-1)*limit).findAll();
        for(const auto& dbUser:dbUsers){
            user u;
            u.id=dbUser.getValueOfId();
            u.name=dbUser.getValueOfUsername();
            u.email=dbUser.getValueOfEmail();
            u.password=dbUser.getValueOfPassword();
            users.push_back(u);
        }
        return users;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return {};
    }
}

user UserRepository::getUser(int id){
    try
    {
        Mapper<Users> mapper(Database::getClient());
        auto dbUser=mapper.findByPrimaryKey(id);
        user u;
        u.id=dbUser.getValueOfId();
        u.name=dbUser.getValueOfUsername();
        u.email=dbUser.getValueOfEmail();
        u.password=dbUser.getValueOfPassword();
        return u;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return {};
    }
}

user UserRepository::getUserByEmail(const std::string& email){
    try
    {
        Mapper<Users> mapper(Database::getClient());
        auto dbUser=mapper.findOne(Criteria(Users::Cols::_email, email));
        user u;
        u.id=dbUser.getValueOfId();
        u.name=dbUser.getValueOfUsername();
        u.email=dbUser.getValueOfEmail();
        u.password=dbUser.getValueOfPassword();
        return u;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return {};
    }
}

bool UserRepository::updateUser(int id,const user& u){
    try
    {
        Mapper<Users> mapper(Database::getClient());
        auto dbUser=mapper.findByPrimaryKey(id);
        dbUser.setUsername(u.name);
        dbUser.setEmail(u.email);
        dbUser.setPassword(u.password);
        mapper.update(dbUser);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool UserRepository::deleteUser(int id){
    try
    {
        Mapper<Users> mapper(Database::getClient());
        auto dbUser=mapper.findByPrimaryKey(id); // Check if the user exists
        if(!dbUser.getId()){
            return false; // User does not exist
        }
        mapper.deleteByPrimaryKey(id);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}