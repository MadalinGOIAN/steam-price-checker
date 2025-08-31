cmake_minimum_required(VERSION 3.16)
project(steam-prices-checker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)

# Fetch libcurl
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(HTTP_ONLY ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG curl-8_8_0
)

FetchContent_MakeAvailable(curl)

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Main executable
add_executable(steam-price-checker src/main.cpp)

target_link_libraries(steam-price-checker
    PRIVATE
        nlohmann_json::nlohmann_json
        libcurl
)

# Tests executable
add_executable(steam-price-checker-tests test/test.cpp)

target_link_libraries(steam-price-checker-tests
    PRIVATE
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(steam-price-checker-tests)