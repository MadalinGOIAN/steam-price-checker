#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Paginator 
{
public:
    Paginator(std::vector<T> items, std::uint16_t pageSize)
        : items(std::move(items)), pageSize(pageSize), currentIndex(0u)
    {
        if (pageSize == 0u)
        {
            throw std::invalid_argument("Page size must be greater than zero");
        }
    }

    bool hasNext() const
    {
        return currentIndex < items.size();
    }

    std::vector<T> next()
    {
        if (!hasNext())
        {
            return {};
        }

        const std::uint16_t start = currentIndex;
        const std::uint16_t end = std::min<size_t>(start + pageSize, items.size());

        currentIndex = end;

        return std::vector<T>(items.begin() + start, items.begin() + end);
    }

    void reset()
    {
        currentIndex = 0u;
    }

private:
    std::vector<T> items;
    std::uint16_t pageSize;
    std::uint16_t currentIndex;
};