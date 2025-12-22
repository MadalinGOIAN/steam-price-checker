#include "SteamGameRepository.hpp"

SteamGameRepository::SteamGameRepository(SteamApiFetcher& fetcher)
	: fetcher(fetcher)
{
}

std::vector<Game> SteamGameRepository::getDiscountedGames() const
{
	return fetcher.fetchDiscountedGames();
}
