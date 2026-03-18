cmake_minimum_required(VERSION 3.15)
project(drogon_jwt_postgres VERSION 1.0.0)

find_package(Drogon REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(libxcrypt REQUIRED)

add_executable(drogon_jwt_postgres
    # config
    ./src/config/database.cc 

    # controllers
    ./src/controllers/health.cc

    # # models
    ./src/models/Users.cc

    # filters
    ./src/filters/AuthFilter.cc

    # services

    # utils
    ./src/utils/token.cc

    # repositories
    ./src/repositories/UserRepository.cc

    # main
    ./src/main.cc)

target_link_libraries(drogon_jwt_postgres PRIVATE
    Drogon::Drogon
    jwt-cpp::jwt-cpp
    libxcrypt::libxcrypt
)