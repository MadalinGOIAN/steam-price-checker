#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "stubs/StubsHttpClient.hpp"
#include "SteamGameRepository.hpp"

using namespace ::testing;

TEST(TestGameRepository, ReturnsGamesFromFetcher) {
    StubCorrectHttpClient stubCorrectHttpClient;
    SteamApiFetcher fetcher(stubCorrectHttpClient);
    SteamGameRepository sut{ fetcher };

    std::vector<Game> expectedGames{
        { "Hollow Knight: Silksong", 59.99, 29.99, 50, "EUR" },
        { "Game B", 40.0, 20.0, 50, "EUR" }
    };

    std::vector result = sut.getDiscountedGames();

    EXPECT_EQ(result.size(), expectedGames.size());

    EXPECT_EQ(result[0].GetName(), expectedGames[0].GetName());
    EXPECT_EQ(result[0].GetDefaultPrice(), expectedGames[0].GetDefaultPrice());
    EXPECT_EQ(result[0].GetCurrentPrice(), expectedGames[0].GetCurrentPrice());
    EXPECT_EQ(result[0].GetDiscount(), expectedGames[0].GetDiscount());
    EXPECT_EQ(result[0].GetCurrency(), expectedGames[0].GetCurrency());
    
    EXPECT_EQ(result[1].GetName(), expectedGames[1].GetName());
    EXPECT_EQ(result[1].GetDefaultPrice(), expectedGames[1].GetDefaultPrice());
    EXPECT_EQ(result[1].GetCurrentPrice(), expectedGames[1].GetCurrentPrice());
    EXPECT_EQ(result[1].GetDiscount(), expectedGames[1].GetDiscount());
    EXPECT_EQ(result[1].GetCurrency(), expectedGames[1].GetCurrency());
}

TEST(TestGameRepository, PropagatesDiscardedDataErrorFromFetcher)
{
    StubDiscardedDataHttpClient stubDiscardedDataHttpClient;
    SteamApiFetcher fetcher(stubDiscardedDataHttpClient);
    SteamGameRepository sut{ fetcher };

    ASSERT_THAT([&sut]() { sut.getDiscountedGames(); },
        ThrowsMessage<std::runtime_error>("Failed to parse JSON")
	);
}

TEST(TestGameRepository, PropagatesInvalidJsonErrorWithoutSpecialFieldFromFetcher)
{
    StubWithoutSpecialFieldHttpClient stubWithoutSpecialFieldHttpClient;
    SteamApiFetcher fetcher(stubWithoutSpecialFieldHttpClient);
    SteamGameRepository sut{ fetcher };

    ASSERT_THAT([&sut]() { sut.getDiscountedGames(); },
        ThrowsMessage<std::runtime_error>("Invalid JSON fields")
	);
}

TEST(TestGameRepository, PropagatesInvalidJsonErrorWithoutItemsFieldFromFetcher)
{
    StubWithoutItemsFieldHttpClient stubWithoutItemsFieldHttpClient;
    SteamApiFetcher fetcher(stubWithoutItemsFieldHttpClient);
    SteamGameRepository sut{ fetcher };

    ASSERT_THAT([&sut]() { sut.getDiscountedGames(); },
        ThrowsMessage<std::runtime_error>("Invalid JSON fields")
	);
}