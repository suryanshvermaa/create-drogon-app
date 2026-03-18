cmake_minimum_required(VERSION 3.15)
project(drogon-s3-starter VERSION 1.0.0)

find_package(Drogon REQUIRED)
find_package(AWSSDK CONFIG REQUIRED)

add_executable(drogon-s3-starter
    # config
    ./src/config/database.cc 

    # controllers
    ./src/controllers/health.cc

    # # models
    ./src/models/Users.cc

    # filters

    # services
    ./src/services/S3Service.cc

    # utils

    # repositories
    ./src/repositories/UserRepository.cc

    # main
    ./src/main.cc)

target_link_libraries(drogon-s3-starter PRIVATE
    Drogon::Drogon
    AWS::aws-sdk-cpp-s3
    AWS::aws-sdk-cpp-core
)