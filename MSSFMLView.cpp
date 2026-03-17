#include <cmath>
#include <SFML/Graphics.hpp>
#include "MSSFMLView.h"
#include "MinesweeperBoard.h"

MSSFMLView::MSSFMLView(MinesweeperBoard &picked_board): board(picked_board)
{
    field_size = 40;
    start = true;
    font.loadFromFile("resources/ARCADECLASSIC.ttf"); // zaczerpniete z internetu
}

void MSSFMLView::draw(sf::RenderWindow &window)
{
    draw_background(window);
    draw_current_view(window);
}

void MSSFMLView::draw_background(sf::RenderWindow &window)
{
    float x_off = x_offset;
    float y_off = y_offset;

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(field_size, field_size));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2);
    background.setFillColor(sf::Color(200, 200, 200));
    background.setPosition(x_off, y_off);

    for(int column=0; column<board.getBoardWidth(); ++column)
    {
        for(int row=0; row<board.getBoardHeight(); ++row)
        {
            background.setPosition(x_off, y_off);
            window.draw(background);
            y_off = y_off + field_size + 2;
        }
        y_off = y_off - (board.getBoardHeight() * (field_size + 2.0f));
        x_off = x_off + field_size + 2;
    }
}

void MSSFMLView::draw_current_view(sf::RenderWindow &window)
{
    float x_off = x_offset;
    float y_off = y_offset;

    for (int column=0; column<board.getBoardWidth(); ++column)
    {
        for(int row=0; row<board.getBoardHeight(); ++row)
        {
            if(!(board.isRevealed(row, column)))
            {
                draw_field(window, x_off, y_off);
            }

            if(!(board.isRevealed(row, column)) and (board.getFieldInfo(row, column) == 'F'))
            {
                draw_flag(window, x_off, y_off);
            }

            if((board.getGameState() != RUNNING) and (board.getFieldInfo(row, column) == 'm'))
            {
                if(board.isRevealed(row, column))
                {
                    draw_explosion(window, x_off, y_off);
                }
                else
                {
                    draw_mine(window, x_off, y_off);
                }
            }
            if((board.isRevealed(row, column)) and (board.getGameState() == RUNNING))
            {
                draw_amount(window, row, column, x_off, y_off);
            }

            if((board.isRevealed(row, column)) and (board.getGameState() == RUNNING))
            {
                draw_amount(window, row, column, x_off, y_off);
            }

            if(board.getGameState() == FINISHED_WIN)
            {
                draw_amount(window, row, column, x_off, y_off);
            }

            y_off = y_off + field_size + 2;
        }
        y_off = y_off - (board.getBoardHeight() * (field_size + 2.0f));
        x_off = x_off + field_size + 2;
    }
}

void MSSFMLView::draw_field(sf::RenderWindow &window, float x_off, int y_off)
{
    sf::RectangleShape field;
    field.setSize(sf::Vector2f(field_size, field_size));
    field.setOutlineColor(sf::Color::White);
    field.setOutlineThickness(2);
    field.setFillColor(sf::Color(128, 128, 128));
    field.setPosition(x_off, y_off);
    window.draw(field);
}

void MSSFMLView::draw_flag(sf::RenderWindow &window, float x_off, int y_off)
{
    sf::CircleShape flag(field_size*0.25f, 3);
    flag.setFillColor(sf::Color(255, 65, 65));
    flag.setRotation(270);
    flag.setPosition(x_off + flag.getRadius(), y_off + ((field_size + flag.getRadius() * 2) / 2) - field_size * 0.1f);
    window.draw(flag);

    sf::RectangleShape flag_pole;
    flag_pole.setSize(sf::Vector2f(field_size*0.05f, field_size*0.66f));
    flag_pole.setOutlineColor(sf::Color::Black);
    flag_pole.setOutlineThickness(0);
    flag_pole.setFillColor(sf::Color(0, 0, 0));
    flag_pole.setPosition(x_off+flag.getRadius()*(1.0f + sqrt(2)), y_off+(field_size-flag.getRadius()*(1.0f+sqrt(2.0)))/2.0f);
    window.draw(flag_pole);
}

void MSSFMLView::draw_mine(sf::RenderWindow &window, float x_off, int y_off)
{
    sf::CircleShape mine;
    mine.setRadius(field_size*0.3f);
    mine.setFillColor(sf::Color(0, 0, 0));
    mine.setOutlineThickness(0);
    mine.setOutlineColor(sf::Color::Black);
    mine.setPosition(x_off + (field_size * 0.2f), y_off + (field_size * 0.2f));

    sf::CircleShape shine;
    shine.setRadius(field_size*0.03f);
    shine.setFillColor(sf::Color(255, 255, 255));
    shine.setOutlineThickness(0);
    shine.setOutlineColor(sf::Color::Black);
    shine.setPosition(x_off + (field_size * 0.55f), y_off + (field_size * 0.35f));

    window.draw(mine);
    window.draw(shine);
}

void MSSFMLView::draw_explosion(sf::RenderWindow &window, float x_off, int y_off)
{
    sf::CircleShape mine;
    mine.setRadius(field_size*0.33f);
    mine.setFillColor(sf::Color(0, 0, 0));
    mine.setOutlineThickness(field_size*0.1);
    mine.setOutlineColor(sf::Color(230, 125, 30));
    mine.setPosition(x_off + (field_size * 0.17f), y_off + (field_size * 0.17f));

    sf::CircleShape shine;
    shine.setRadius(field_size*0.03f);
    shine.setFillColor(sf::Color(255, 255, 255));
    shine.setOutlineThickness(0);
    shine.setOutlineColor(sf::Color::Black);
    shine.setPosition(x_off + (field_size * 0.55f), y_off + (field_size * 0.35f));

    window.draw(mine);
    window.draw(shine);
}


void MSSFMLView::draw_amount(sf::RenderWindow &window, int row, int column, float x_off, float y_off)
{
    sf::RectangleShape vertical;
    vertical.setOutlineThickness(0);

    sf::RectangleShape horizontal;
    horizontal.setOutlineThickness(0);

    sf::RectangleShape diagonal;
    diagonal.setOutlineThickness(0);

    switch(board.countMines(row, column))
    {
        case 1:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.6f));
            vertical.setFillColor(sf::Color(0, 128, 255));
            vertical.setPosition(x_off + (field_size * 0.55f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            diagonal.setSize(sf::Vector2f(field_size*0.1f, field_size*0.37f));
            diagonal.setFillColor(sf::Color(0, 128, 255));
            diagonal.setPosition(x_off + (field_size * 0.55f), y_off + (field_size * 0.2f));
            diagonal.setRotation(37);
            window.draw(diagonal);
            break;
        }

        case 2:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.3f));
            vertical.setFillColor(sf::Color(50, 210, 110));
            vertical.setPosition(x_off + (field_size * 0.6f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            vertical.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.5f));
            window.draw(vertical);

            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(50, 210, 110));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.45f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.7f));
            window.draw(horizontal);
            break;
        }

        case 3:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.6f));
            vertical.setFillColor(sf::Color(255, 0, 0));
            vertical.setPosition(x_off + (field_size * 0.6f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(255, 0, 0));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.7f));
            window.draw(horizontal);

            horizontal.setSize(sf::Vector2f(field_size*0.3f, field_size*0.1f));
            horizontal.setPosition(x_off + (field_size * 0.4f), y_off + (field_size * 0.45f));
            window.draw(horizontal);
            break;
        }

        case 4:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.3f));
            vertical.setFillColor(sf::Color(255, 255, 50));
            vertical.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.6f));
            vertical.setPosition(x_off + (field_size * 0.6f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(255, 255, 50));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.45f));
            window.draw(horizontal);
            break;
        }

        case 5:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.3f));
            vertical.setFillColor(sf::Color(255, 180, 85));
            vertical.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            vertical.setPosition(x_off + (field_size * 0.6f), y_off + (field_size * 0.5f));
            window.draw(vertical);

            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(255, 180, 85));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.45f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.7f));
            window.draw(horizontal);
            break;
        }

        case 6:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.6f));
            vertical.setFillColor(sf::Color(255, 0, 255));
            vertical.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.3f));
            vertical.setPosition(x_off + (field_size * 0.6f), y_off + (field_size * 0.45f));
            window.draw(vertical);


            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(255, 0, 255));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.45f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.7f));
            window.draw(horizontal);
            break;
        }

        case 7:
        {
            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(140, 100, 45));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(horizontal);

            diagonal.setSize(sf::Vector2f(field_size*0.1f, field_size*0.65f));
            diagonal.setFillColor(sf::Color(140, 100, 45));
            diagonal.setPosition(x_off + (field_size * 0.7f), y_off + (field_size * 0.2f));
            diagonal.setRotation(25);
            window.draw(diagonal);
            break;
        }

        case 8:
        {
            vertical.setSize(sf::Vector2f(field_size*0.1f, field_size*0.6f));
            vertical.setFillColor(sf::Color(0, 100, 50));
            vertical.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(vertical);

            vertical.setPosition(x_off + (field_size * 0.6f), y_off + (field_size * 0.2f));
            window.draw(vertical);


            horizontal.setSize(sf::Vector2f(field_size*0.4f, field_size*0.1f));
            horizontal.setFillColor(sf::Color(0, 100, 50));
            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.2f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.45f));
            window.draw(horizontal);

            horizontal.setPosition(x_off + (field_size * 0.3f), y_off + (field_size * 0.7f));
            window.draw(horizontal);
            break;
        }
    }
}

void MSSFMLView::draw_new_game_box(sf::RenderWindow &window)
{
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(100, 40));
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(4);
    box.setFillColor(sf::Color(255, 90, 80));
    box.setPosition(350,750);
    window.draw(box);
}

float MSSFMLView::get_x_offset()
{
    return x_offset;
}

float MSSFMLView::get_y_offset()
{
    return y_offset;
}

float MSSFMLView::get_field_size()
{
    return field_size;
}

void MSSFMLView::draw_text(sf::RenderWindow &window)
{
    sf::Text text;
    text.setFont(font);
    text.setString("MINESWEEPER");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setPosition(225, 0);

    sf::Text status;
    status.setFont(font);
    status.setCharacterSize(60);
    status.setPosition(275, 0);

    sf::Text again;
    again.setFont(font);
    again.setFillColor(sf::Color::Black);
    again.setCharacterSize(40);
    again.setPosition(150, 700);
    again.setString("PRESS  HERE  TO  PLAY  AGAIN");

    sf::Text right_mouse;
    right_mouse.setFont(font);
    right_mouse.setFillColor(sf::Color::Black);
    right_mouse.setCharacterSize(30);
    right_mouse.setPosition(100, 700);
    right_mouse.setString("PRESS  RIGHT  MOUSE  TO  REVEAL  FIELD");

    sf::Text left_mouse;
    left_mouse.setFont(font);
    left_mouse.setFillColor(sf::Color::Black);
    left_mouse.setCharacterSize(30);
    left_mouse.setPosition(100, 740);
    left_mouse.setString("PRESS  LEFT  MOUSE  TO   TOGGLE  FIELD");


    switch(board.getGameState())
    {
        case 0:
        {
            window.draw(text);
            window.draw(right_mouse);
            window.draw(left_mouse);
            break;
        }
        case 1:
        {
            status.setFillColor(sf::Color::Green);
            status.setString("YOU  WON");
            window.draw(status);
            window.draw(again);
            draw_new_game_box(window);
            break;
        }
        case 2:
        {
            status.setFillColor(sf::Color::Red);
            status.setString("YOU  LOST");
            window.draw(status);
            window.draw(again);
            draw_new_game_box(window);
            break;
        }
    }
}

void MSSFMLView::set_board(MinesweeperBoard &new_board)
{
    board = new_board;
    start = false;
}

bool MSSFMLView::is_it_start()
{
    return start;
}

void MSSFMLView::set_start()
{
    start = true;
}

void MSSFMLView::reset_start()
{
    start = false;
}

void MSSFMLView::set_field_size()
{
    if(((800.0f - 2 * y_offset) / (board.getBoardHeight() + 1.0f)) < ((800.0f - 2 * x_offset) / (board.getBoardWidth() + 1.0f)))
    {
        field_size = (800.0f - 2 * y_offset) / (board.getBoardHeight() + 1.0f);
    }
    else
    {
        field_size = (800.0f - 2 * x_offset) / (board.getBoardWidth() + 1.0f);
    }
    // powyzszy kod determinuje jak duze bedzie pojedyncze pole na planszy - pozwala tworzyc calkiem duze plansze,
    // wysypuje sie dopiero gdy w konstruktorze MinesweeperBoard jako argumenty height i width damy 55 i 55
    // wtedy co prawda pola sa bardzo male ale nadal da sie na nich grac
    // w rzeczywistosci byloby bardziej przydatne gdyby gracz mial wybor wielkosci planszy
    // jednakze rozmiary planszy sa odgornie ustalone (w moim rozwiazaniu sapera)
}

void MSSFMLView::draw_start(sf::RenderWindow &window)
{
    sf::Text intro;
    intro.setFont(font);
    intro.setString("CHOOSE  GAMEMODE  BY");
    intro.setFillColor(sf::Color::Black);
    intro.setCharacterSize(60);
    intro.setPosition(100, 50);

    sf::Text intro2;
    intro2.setFont(font);
    intro2.setString("CLICKING  A  BOX");
    intro2.setFillColor(sf::Color::Black);
    intro2.setCharacterSize(60);
    intro2.setPosition(150, 120);

    sf::Text easy;
    easy.setFont(font);
    easy.setString("EASY");
    easy.setFillColor(sf::Color(60, 200, 40));
    easy.setCharacterSize(60);
    easy.setPosition(175, 250);

    sf::RectangleShape box_easy;
    box_easy.setSize(sf::Vector2f(100, 60));
    box_easy.setOutlineColor(sf::Color::Black);
    box_easy.setOutlineThickness(4);
    box_easy.setFillColor(sf::Color(60, 200, 40));
    box_easy.setPosition(450,260);

    sf::Text normal;
    normal.setFont(font);
    normal.setString("NORMAL");
    normal.setFillColor(sf::Color::Blue);
    normal.setCharacterSize(60);
    normal.setPosition(175, 400);

    sf::RectangleShape box_normal;
    box_normal.setSize(sf::Vector2f(100, 60));
    box_normal.setOutlineColor(sf::Color::Black);
    box_normal.setOutlineThickness(4);
    box_normal.setFillColor(sf::Color::Blue);
    box_normal.setPosition(450,410);

    sf::Text hard;
    hard.setFont(font);
    hard.setString("HARD");
    hard.setFillColor(sf::Color::Red);
    hard.setCharacterSize(60);
    hard.setPosition(175, 550);

    sf::RectangleShape box_hard;
    box_hard.setSize(sf::Vector2f(100, 60));
    box_hard.setOutlineColor(sf::Color::Black);
    box_hard.setOutlineThickness(4);
    box_hard.setFillColor(sf::Color::Red);
    box_hard.setPosition(450,560);

    window.draw(intro);
    window.draw(intro2);
    window.draw(easy);
    window.draw(box_easy);
    window.draw(normal);
    window.draw(box_normal);
    window.draw(hard);
    window.draw(box_hard);
}
