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
    
RUN pip3 install conan
WORKDIR /app
COPY conanfile.txt .
COPY CMakeLists.txt .
RUN conan profile detect --force
RUN conan install . --output-folder=build --build=missing -s build_type=Release

COPY src/ src/
RUN pip3 install cmake
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

# App binary is produced at /app/build/Drogon_Starter with the conan-release preset
COPY --from=builder /app/build/Drogon_Starter /app/Drogon_Starter

# Ship a default config; override by mounting your own /app/config/config.json
COPY config/config.example.json /app/config/config.json

EXPOSE 3000

CMD ["/app/Drogon_Starter"]