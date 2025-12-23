#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SteamApiFetcher.hpp"
#include "mocks/MockHttpClient.hpp"

using namespace ::testing;

class TestSteamApiFetcher : public Test
{
protected:
	void SetUp() override
	{
		sut = new SteamApiFetcher(mockHttpClient);
	}

	void TearDown() override
	{
		delete sut;
	}

	MockHttpClient mockHttpClient;
	SteamApiFetcher* sut;
};

TEST_F(TestSteamApiFetcher, ParsesSingleDiscountedGameCorrectly)
{
    const std::string correctSingleItemJson{ R"(
    {
      "specials": {
        "items": [
          {
            "name": "Hollow Knight: Silksong",
            "original_price": 5999,
            "final_price": 2999,
            "discount_percent": 50,
            "currency": "EUR"
          }
        ]
      }
    })" };

    EXPECT_CALL(mockHttpClient, get(_))
        .WillOnce(Return(correctSingleItemJson));

    std::vector<Game> games = sut->fetchDiscountedGames();

    ASSERT_EQ(1u, games.size());
    EXPECT_EQ("Hollow Knight: Silksong", games[0].getName());
    EXPECT_DOUBLE_EQ(59.99, games[0].getDefaultPrice());
    EXPECT_DOUBLE_EQ(29.99, games[0].getCurrentPrice());
    EXPECT_EQ(50, games[0].getDiscount());
	EXPECT_EQ("EUR", games[0].getCurrency());
}

TEST_F(TestSteamApiFetcher, ParsesMultipleDiscountedGamesCorrectly)
{
    const std::string correctMultipleItemsJson{ R"(
    {
      "specials": {
        "items": [
          {
            "name": "Hollow Knight: Silksong",
            "original_price": 5999,
            "final_price": 2999,
            "discount_percent": 50,
            "currency": "EUR"
          },
          {
            "name": "Game 2",
            "original_price": 3999,
            "final_price": 1999,
            "discount_percent": 50,
            "currency": "USD"
          },
          {
            "name": "Game 3",
            "original_price": 1999,
            "final_price": 999,
            "discount_percent": 50,
            "currency": "GBP"
          }
        ]
      }
    })" };

    EXPECT_CALL(mockHttpClient, get(_))
        .WillOnce(Return(correctMultipleItemsJson));

    std::vector<Game> games = sut->fetchDiscountedGames();

    ASSERT_EQ(3u, games.size());
}

TEST_F(TestSteamApiFetcher, DiscardedDataThrowsException)
{
    EXPECT_CALL(mockHttpClient, get(_))
        .WillOnce(Return(""));

    try
    {

    sut->fetchDiscountedGames();
    FAIL() << "Expected std::runtime_error";

    }
    catch (const std::runtime_error& ex)
    {
        EXPECT_STREQ(ex.what(), "Failed to parse JSON");
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error, got different exception";
    }
}

TEST_F(TestSteamApiFetcher, DataWithoutSpecialSectionThrowsException)
{
    const std::string jsonWithousSpecialSection{ R"(
    {
      "items": [
        {
            "name": "Hollow Knight: Silksong",
            "original_price": 5999,
            "final_price": 2999,
            "discount_percent": 50,
            "currency": "EUR"
        }
      ]
    })" };

    EXPECT_CALL(mockHttpClient, get(_))
        .WillOnce(Return(jsonWithousSpecialSection));

    try
    {

    sut->fetchDiscountedGames();
    FAIL() << "Expected std::runtime_error";

    }
    catch (const std::runtime_error& ex)
    {
        EXPECT_STREQ(ex.what(), "Invalid JSON fields");
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error, got different exception";
    }
}

TEST_F(TestSteamApiFetcher, DataWithoutItemsSectionThrowsException)
{
    const std::string jsonWithousItemsSection{ R"(
    {
      "specials": {
        "name": "Hollow Knight: Silksong",
        "original_price": 5999,
        "final_price": 2999,
        "discount_percent": 50,
        "currency": "EUR"
      }
    })" };

    EXPECT_CALL(mockHttpClient, get(_))
        .WillOnce(Return(jsonWithousItemsSection));

    try
    {

    sut->fetchDiscountedGames();
    FAIL() << "Expected std::runtime_error";

    }
    catch (const std::runtime_error& ex)
    {
        EXPECT_STREQ(ex.what(), "Invalid JSON fields");
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error, got different exception";
    }
}