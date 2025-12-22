add_library(steam-price-checker-lib
    Game.cpp
    HttpClient.cpp
    SteamApiFetcher.cpp
    SteamGameRepository.cpp)

target_include_directories(steam-price-checker-lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(steam-price-checker-lib
    PUBLIC 
        nlohmann_json::nlohmann_json
        libcurl
)

add_executable(steam-price-checker main.cpp)
target_link_libraries(steam-price-checker PRIVATE steam-price-checker-lib)
