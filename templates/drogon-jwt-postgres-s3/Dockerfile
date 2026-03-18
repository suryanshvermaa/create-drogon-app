FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    curl \
    python3 \
    python3-pip \
    pkg-config \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*
RUN pip3 install cmake
RUN pip3 install conan
WORKDIR /app
COPY conanfile.txt .
COPY CMakeLists.txt .
RUN conan profile detect --force
RUN conan install . --output-folder=build --build=missing -s build_type=Release -c tools.system.package_manager:mode=install

COPY src/ src/
COPY scripts/ scripts/
RUN cmake --preset conan-release
RUN cmake --build --preset conan-release

FROM ubuntu:22.04 AS runtime
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    openssl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
RUN mkdir -p /app/config
COPY --from=builder /app/build/drogon_jwt_postgres_s3 /app/build/drogon_jwt_postgres_s3

EXPOSE 8080

CMD ["/app/build/drogon_jwt_postgres_s3"]