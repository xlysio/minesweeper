#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#ifndef SAPER_MSSFMLCONTROLLER_H
#define SAPER_MSSFMLCONTROLLER_H


class MSSFMLController
{
    MinesweeperBoard &board;
    MSSFMLView &view;

public:
    MSSFMLController(MinesweeperBoard &picked_board, MSSFMLView &picked_view);
    void play(sf::Event &event, sf::RenderWindow &window);
    void set_board(sf::Event &event, sf::RenderWindow &window);
};


#endif //SAPER_MSSFMLCONTROLLER_H
