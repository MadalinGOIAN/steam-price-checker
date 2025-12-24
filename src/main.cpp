#include <iostream>
#include <conio.h>

#include "HttpClient.hpp"
#include "SteamApiFetcher.hpp"
#include "SteamGameRepository.hpp"
#include "Paginator.hpp"

#include "utils/Print.hpp"

int main()
{
    try
    {
        HttpClient httpClient;
        SteamApiFetcher apiFetcher(httpClient);
        SteamGameRepository repository(apiFetcher);

        std::vector<Game> games = repository.getDiscountedGames();

        if (games.empty())
        {
            std::cout << "No discounted games found.\n";
            return 0;
        }

        Paginator<Game> paginator(std::move(games), 4u);

        while (paginator.hasNext())
        {
            std::vector<Game> page = paginator.next();
            printGames(page);

            if (!paginator.hasNext())
            {
                std::cout << "\nEnd of results.\n";
                _getch();
                break;
            }

            std::cout << "\nPress any key to see more...\n";
            _getch();
			system("cls");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
