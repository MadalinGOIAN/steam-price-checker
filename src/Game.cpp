#include "Game.hpp"

Game::Game(
	std::string name,
	double defaultPrice,
	double currentPrice,
	int8_t discount,
	std::string currency)
	: name(std::move(name)),
	  defaultPrice(std::move(defaultPrice)),
	  currentPrice(std::move(currentPrice)),
	  discount(std::move(discount)),
	  currency(std::move(currency))
{
}

std::string Game::getName() const
{
	return name;
}

double Game::getDefaultPrice() const
{
	return defaultPrice;
}

double Game::getCurrentPrice() const
{
	return currentPrice;
}

int8_t Game::getDiscount() const
{
	return discount;
}

std::string Game::getCurrency() const
{
	return currency;
}
