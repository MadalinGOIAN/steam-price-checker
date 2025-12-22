#pragma once

#include <vector>
#include "itf/IHttpClient.hpp"
#include "Game.hpp"

class SteamApiFetcher
{
public:
    explicit SteamApiFetcher(const IHttpClient&);
    std::vector<Game> fetchDiscountedGames() const;

private:
    const IHttpClient& httpClient;
};
