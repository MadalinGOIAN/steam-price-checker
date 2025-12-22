#pragma once

#include "itf/IGameRepository.hpp"
#include "SteamApiFetcher.hpp"

class SteamGameRepository : public IGameRepository
{
public:
    explicit SteamGameRepository(SteamApiFetcher&);
    std::vector<Game> getDiscountedGames() const override;

private:
    SteamApiFetcher& fetcher;
};