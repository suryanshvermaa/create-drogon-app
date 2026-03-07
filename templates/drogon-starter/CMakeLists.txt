cmake_minimum_required(VERSION 3.15)
project(Drogon_Starter VERSION 1.0.0)

find_package(Drogon REQUIRED)

add_executable(Drogon_Starter
    # config
    ./src/database/database.cc 

    # controllers
    ./src/controllers/health.cc

    # # models
    ./src/models/Users.cc

    # repositories
    ./src/repositories/UserRepository.cc

    # main
    ./src/main.cc)

target_link_libraries(Drogon_Starter PRIVATE
    Drogon::Drogon
)