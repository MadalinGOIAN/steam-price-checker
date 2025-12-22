add_executable(steam-price-checker-tests
	TestGame.cpp 
	TestSteamApiFetcher.cpp
	TestSteamGameRepository.cpp)

target_link_libraries(steam-price-checker-tests 
	PRIVATE 
		steam-price-checker-lib
		gtest_main
		gmock
)

include(GoogleTest)
gtest_discover_tests(steam-price-checker-tests)
