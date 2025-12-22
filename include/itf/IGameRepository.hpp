#pragma once

#include <vector>
#include "Game.hpp"

class IGameRepository
{
public:
    virtual std::vector<Game> getDiscountedGames() const = 0;
    virtual ~IGameRepository() = default;
};