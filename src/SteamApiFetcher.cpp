#include <nlohmann/json.hpp>
#include <iostream>
#include "SteamApiFetcher.hpp"

using json = nlohmann::json;

namespace
{
const std::string steamUrl{ "https://store.steampowered.com/api/featuredcategories" };
}

SteamApiFetcher::SteamApiFetcher(const IHttpClient& client)
	: httpClient(client)
{
}

std::vector<Game> SteamApiFetcher::fetchDiscountedGames() const
{
	std::vector<Game> games{};

	std::string response = httpClient.get(steamUrl);
	json data = json::parse(response, nullptr, false);

	if (data.is_discarded())
	{
		throw std::runtime_error("Failed to parse JSON");
	}

	if (!data.contains("specials") || !data["specials"].contains("items"))
	{
		throw std::runtime_error("Invalid JSON fields");
	}

	for (const auto& item : data["specials"]["items"])
	{
		std::string name = item.value<std::string>("name", "string");
		double defaultPrice = item.value<int>("original_price", 0) / 100.0;
		double currentPrice = item.value<int>("final_price", 0) / 100.0;
		int8_t discount = item.value<int8_t>("discount_percent", 0);
		std::string currency = item.value<std::string>("currency", "string");

		games.emplace_back(name, defaultPrice, currentPrice, discount, currency);
	}

	return games;
}
