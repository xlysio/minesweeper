#include <iostream>
#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 800), "Grafika w C++/SFML");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    MinesweeperBoard board;
    MSSFMLView view (board);
    MSSFMLController ctrl(board, view);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(view.is_it_start())
        {
            window.clear(sf::Color(200, 200, 200));
            ctrl.set_board(event, window);
            window.display();
        }
        else
        {
            window.clear(sf::Color(200, 200, 200));
            ctrl.play(event, window);
            window.display();
        }
    }

    return 0;
}
