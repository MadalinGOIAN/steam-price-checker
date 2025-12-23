#pragma once

#include <string>
#include <cstdint>

class Game
{
public:
	Game(std::string, double, double, int8_t, std::string);

    std::string getName() const;
    double getDefaultPrice() const;
    double getCurrentPrice() const;
    int8_t getDiscount() const;
    std::string getCurrency() const;

private:
    std::string name;
    double defaultPrice;
    double currentPrice;
    int8_t discount;
    std::string currency;
};
