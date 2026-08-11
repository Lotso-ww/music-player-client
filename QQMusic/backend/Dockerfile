FROM ubuntu:24.04 AS build

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake git ca-certificates pkg-config \
    libjsoncpp-dev uuid-dev libssl-dev zlib1g-dev libbrotli-dev \
    default-libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

ARG DROGON_VERSION=v1.9.10
ARG DROGON_REPOSITORY=https://gitee.com/mirrors/drogon.git
ARG TRANTOR_REPOSITORY=https://ghproxy.net/https://github.com/an-tao/trantor.git
RUN git config --global url."${TRANTOR_REPOSITORY}".insteadOf "https://github.com/an-tao/trantor.git" \
    && git clone --depth 1 --branch ${DROGON_VERSION} --recurse-submodules --shallow-submodules \
        ${DROGON_REPOSITORY} /tmp/drogon \
    && cmake -S /tmp/drogon -B /tmp/drogon/build \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_ORM=ON \
        -DMYSQL_INCLUDE_DIRS=/usr/include/mysql \
        -DMYSQL_LIBRARIES=/usr/lib/x86_64-linux-gnu/libmysqlclient.so \
        -DBUILD_CTL=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTING=OFF \
    && cmake --build /tmp/drogon/build --parallel 2 \
    && cmake --install /tmp/drogon/build \
    && rm -rf /tmp/drogon

WORKDIR /src
COPY CMakeLists.txt ./
COPY src ./src
COPY tests ./tests
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DQQMUSIC_BACKEND_BUILD_TESTS=ON \
    && cmake --build build --parallel 2 \
    && ctest --test-dir build --output-on-failure

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    libjsoncpp25 libssl3t64 libbrotli1 libmysqlclient21 libuuid1 zlib1g \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /usr/local/lib/libdrogon.so* /usr/local/lib/
COPY --from=build /usr/local/lib/libtrantor.so* /usr/local/lib/
COPY --from=build /src/build/qqmusic-api /usr/local/bin/qqmusic-api
RUN ldconfig

EXPOSE 8080
USER nobody
ENTRYPOINT ["/usr/local/bin/qqmusic-api"]
