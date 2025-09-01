add_library(Game Game.cpp)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(steam-price-checker main.cpp)
target_link_libraries(steam-price-checker 
    PRIVATE 
        Game
        nlohmann_json::nlohmann_json
        libcurl)