add_executable(steam-price-checker-tests TestGame.cpp)

target_link_libraries(steam-price-checker-tests 
	PRIVATE 
		Game
		gtest_main)

include(GoogleTest)
gtest_discover_tests(steam-price-checker-tests)