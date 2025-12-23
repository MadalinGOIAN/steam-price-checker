#include <gtest/gtest.h>
#include "Paginator.hpp"
#include "Game.hpp"

class TestPaginator : public ::testing::Test 
{
protected:
	void SetUp()
	{
		Game game("Game", 50.0, 25.0, 50, "USD");
		std::vector<Game> games(25, game);

		sut = new Paginator<Game>(games, 10u);
	}

	void TearDown()
	{
		delete sut;
	}

	Paginator<Game>* sut;
};

TEST_F(TestPaginator, FirstPageHasPageSizeElements) 
{
	std::vector<Game> page = sut->next();

	ASSERT_TRUE(sut->hasNext());

	EXPECT_EQ(page.size(), 10);
	EXPECT_EQ(page[0].getName(), "Game");
	EXPECT_EQ(page[0].getDefaultPrice(), 50.0);
	EXPECT_EQ(page[0].getCurrentPrice(), 25.0);
	EXPECT_EQ(page[0].getDiscount(), 50);
	EXPECT_EQ(page[0].getCurrency(), "USD");
}

TEST_F(TestPaginator, LastPageContainsRemainingElements) 
{
	sut->next();
	sut->next();
	std::vector<Game> lastPage = sut->next();

	ASSERT_FALSE(sut->hasNext());

	EXPECT_EQ(lastPage.size(), 5u);
	EXPECT_EQ(lastPage[0].getName(), "Game");
	EXPECT_EQ(lastPage[0].getDefaultPrice(), 50.0);
	EXPECT_EQ(lastPage[0].getCurrentPrice(), 25.0);
	EXPECT_EQ(lastPage[0].getDiscount(), 50);
	EXPECT_EQ(lastPage[0].getCurrency(), "USD");
}

TEST_F(TestPaginator, NextReturnsEmptyWhenNoMorePages) 
{
	sut->next();
	sut->next();
	sut->next();
	std::vector<Game> emptyPage = sut->next();

	ASSERT_TRUE(emptyPage.empty());
	ASSERT_FALSE(sut->hasNext());
}

TEST_F(TestPaginator, HasNextReflectsStateCorrectly) 
{
	EXPECT_TRUE(sut->hasNext());
	sut->next();
	EXPECT_TRUE(sut->hasNext());
	sut->next();
	EXPECT_TRUE(sut->hasNext());
	sut->next();
	EXPECT_FALSE(sut->hasNext());
}

TEST_F(TestPaginator, ResetRestartsPagination)
{
	sut->next();
	sut->next();
	sut->next();
	sut->next();

	EXPECT_FALSE(sut->hasNext());

	sut->reset();

	EXPECT_TRUE(sut->hasNext());

	std::vector<Game> page = sut->next();

	ASSERT_EQ(page.size(), 10u);
}