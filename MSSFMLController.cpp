#include "MSSFMLController.h"
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#include <SFML/Graphics.hpp>
#include <thread> // zaczerpniete z internetu wykorzystywane w celu zatrzymania dzialania programu na chwile
#include <chrono>

MSSFMLController::MSSFMLController(MinesweeperBoard &picked_board, MSSFMLView &picked_view): board(picked_board), view(picked_view)
{

}

void MSSFMLController::play(sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        int row = (event.mouseButton.y - view.get_y_offset()) / (view.get_field_size() + 2);
        int column = (event.mouseButton.x - view.get_x_offset()) / (view.get_field_size() + 2);

        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        if (event.mouseButton.button == sf::Mouse::Left)
        {
            board.revealField(row, column);
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            board.toggleFlag(row, column);
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // potrzebne, gdyz w przeciwnym razie flaga "miga", nie ustawia sie poprawnie
        }

        if((x >= 350) and (x <= 450) and (y >=750) and (y <=790) and board.getGameState() != RUNNING)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            view.set_start();
        }
    }

    view.draw(window);
    view.draw_text(window);
}

void MSSFMLController::set_board(sf::Event &event, sf::RenderWindow &window)
{
    view.draw_start(window);
    if (event.type == sf::Event::MouseButtonPressed)
    {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        if((x >= 450) and (x <= 550) and (y >= 260) and (y <= 320))
        {
            MinesweeperBoard new_board(15, 15, EASY);
            view.set_board(new_board);
            board = new_board;
            view.reset_start();
        }
        if((x >= 450) and (x <= 550) and (y >= 410) and (y <= 470))
        {
            MinesweeperBoard new_board(15, 15, NORMAL);
            view.set_board(new_board);
            board = new_board;
            view.reset_start();
        }

        if((x >= 450) and (x <= 550) and (y >= 560) and (y <= 620))
        {
            MinesweeperBoard new_board(15, 15, HARD);
            view.set_board(new_board);
            board = new_board;
            view.reset_start();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        view.set_field_size();
    }
}

