#include <gtest/gtest.h>
#include "Game.hpp"

namespace
{
const std::string name{ "Hollow Knight: Silksong" };
constexpr double defaultPrice{ 20.0 };
constexpr double currentPrice{ 10.0 };
constexpr int8_t discount{ 50 };
const std::string currency{ "EUR" };
}

class TestGame : public ::testing::Test
{
protected:
	void SetUp()
	{
		sut = new Game(name, defaultPrice, currentPrice, discount, currency);
	}

	void TearDown()
	{
		delete sut;
	}

	Game* sut;
};

TEST_F(TestGame, TestGetName)
{
	ASSERT_EQ(name, sut->getName());
}

TEST_F(TestGame, TestGetDefaultPrice)
{
	ASSERT_EQ(defaultPrice, sut->getDefaultPrice());
}

TEST_F(TestGame, TestGetCurrentPrice)
{
	ASSERT_EQ(currentPrice, sut->getCurrentPrice());
}

TEST_F(TestGame, TestGetDiscount)
{
	ASSERT_EQ(discount, sut->getDiscount());
}

TEST_F(TestGame, TestGetCurrency)
{
	ASSERT_EQ(currency, sut->getCurrency());
}
