cmake_minimum_required(VERSION 3.15)
project(drogon_jwt_postgres_s3 VERSION 1.0.0)

find_package(Drogon REQUIRED)
find_package(AWSSDK CONFIG REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(libxcrypt REQUIRED)

add_executable(drogon_jwt_postgres_s3
    # config
    ./src/config/database.cc 

    # controllers
    ./src/controllers/health.cc

    # # models
    ./src/models/Users.cc

    # filters
    ./src/filters/AuthFilter.cc

    # services
    ./src/services/S3Service.cc

    # utils
    ./src/utils/token.cc

    # repositories
    ./src/repositories/UserRepository.cc

    # main
    ./src/main.cc)

target_link_libraries(drogon_jwt_postgres_s3 PRIVATE
    Drogon::Drogon
    AWS::aws-sdk-cpp-s3
    AWS::aws-sdk-cpp-core
    jwt-cpp::jwt-cpp
    libxcrypt::libxcrypt
)