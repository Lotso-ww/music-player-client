cmake_minimum_required(VERSION 3.20)

project(qqmusic_backend LANGUAGES CXX)

option(QQMUSIC_BACKEND_BUILD_TESTS "Build QQMusic backend contract tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)

add_library(qqmusic_backend_core
    src/api_response.cc
    src/config.cc
    src/health_service.cc
    src/log_sanitizer.cc
    src/request_id.cc
)

target_include_directories(qqmusic_backend_core PUBLIC src)
target_link_libraries(qqmusic_backend_core PUBLIC Drogon::Drogon)

target_compile_options(qqmusic_backend_core PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

add_executable(qqmusic-api src/main.cc)
target_link_libraries(qqmusic-api PRIVATE qqmusic_backend_core)

include(CTest)
if(BUILD_TESTING AND QQMUSIC_BACKEND_BUILD_TESTS)
    add_executable(qqmusic_backend_tests tests/api_contract_test.cc)
    target_link_libraries(qqmusic_backend_tests PRIVATE qqmusic_backend_core)
    add_test(NAME qqmusic_backend_contract COMMAND qqmusic_backend_tests)
endif()
