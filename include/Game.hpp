#pragma once

#include <string>
#include <cstdint>

class Game
{
public:
	Game(std::string, double, double, int8_t, std::string);

    std::string GetName() const;
    double GetDefaultPrice() const;
    double GetCurrentPrice() const;
    int8_t GetDiscount() const;
    std::string GetCurrency() const;

private:
    std::string name;
    double defaultPrice;
    double currentPrice;
    int8_t discount;
    std::string currency;
};
