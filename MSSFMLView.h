#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#ifndef LAB2_MSSFMLVIEW_H
#define LAB2_MSSFMLVIEW_H

class MSSFMLView
{
    MinesweeperBoard &board;
    float x_offset = 100.0f;
    float y_offset = 100.0f;
    float field_size;
    bool start;
    sf::Font font;

    void draw_current_view(sf::RenderWindow &window);
    void draw_background(sf::RenderWindow &window);
    void draw_amount(sf::RenderWindow &window, int row, int column, float x_off, float y_off);
    void draw_field(sf::RenderWindow &window, float x_off, int y_off);
    void draw_flag(sf::RenderWindow &window, float x_off, int y_off);
    void draw_mine(sf::RenderWindow &window, float x_off, int y_off);
    void draw_explosion(sf::RenderWindow &window, float x_off, int y_off);
    void draw_new_game_box(sf::RenderWindow &window);

public:
    MSSFMLView(MinesweeperBoard &picked_board);
    void draw(sf::RenderWindow &window);
    void draw_text(sf::RenderWindow &window);
    float get_x_offset();
    float get_y_offset();
    float get_field_size();
    void set_board(MinesweeperBoard &new_board);
    bool is_it_start();
    void set_start();
    void reset_start();
    void set_field_size();
    void draw_start(sf::RenderWindow &window);
};


#endif //LAB2_MSSFMLVIEW_H
