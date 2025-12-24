#pragma once

#include <iostream>
#include <vector>
#include "Game.hpp"

void printGames(const std::vector<Game>& games) {
    std::cout << "\n----------------------------------\n";

    for (const auto& game : games)
    {
        std::cout
            << "Name: " << game.getName() << '\n'
            << "Original Price: " << game.getDefaultPrice() << ' ' << game.getCurrency() << '\n'
            << "Discounted Price: " << game.getCurrentPrice() << ' ' << game.getCurrency() << '\n'
            << "Discount: " << static_cast<int>(game.getDiscount()) << "%\n"
            << "----------------------------------\n";
    }
}