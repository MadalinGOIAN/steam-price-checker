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

std::string Game::GetName() const
{
	return name;
}

double Game::GetDefaultPrice() const
{
	return defaultPrice;
}

double Game::GetCurrentPrice() const
{
	return currentPrice;
}

int8_t Game::GetDiscount() const
{
	return discount;
}

std::string Game::GetCurrency() const
{
	return currency;
}