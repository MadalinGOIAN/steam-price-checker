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

    EXPECT_EQ(result[0].getName(), expectedGames[0].getName());
    EXPECT_EQ(result[0].getDefaultPrice(), expectedGames[0].getDefaultPrice());
    EXPECT_EQ(result[0].getCurrentPrice(), expectedGames[0].getCurrentPrice());
    EXPECT_EQ(result[0].getDiscount(), expectedGames[0].getDiscount());
    EXPECT_EQ(result[0].getCurrency(), expectedGames[0].getCurrency());
    
    EXPECT_EQ(result[1].getName(), expectedGames[1].getName());
    EXPECT_EQ(result[1].getDefaultPrice(), expectedGames[1].getDefaultPrice());
    EXPECT_EQ(result[1].getCurrentPrice(), expectedGames[1].getCurrentPrice());
    EXPECT_EQ(result[1].getDiscount(), expectedGames[1].getDiscount());
    EXPECT_EQ(result[1].getCurrency(), expectedGames[1].getCurrency());
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