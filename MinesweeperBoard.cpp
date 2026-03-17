#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "MinesweeperBoard.h"

using namespace std;

MinesweeperBoard::MinesweeperBoard()
{
    width = 5;
    height = 7;
    moves = 0;
    revealed_fields = 0;
    mode = DEBUG;
    state = RUNNING;

    empty_board();

    data[0][0].hasMine = true;
    data[0][0].hasFlag = false;
    data[0][0].isRevealed = false;
    data[1][1].hasMine = false;
    data[1][1].hasFlag = false;
    data[1][1].isRevealed = true;
    data[0][2].hasMine = true;
    data[0][2].hasFlag = true;
    data[0][2].isRevealed = false;
}

MinesweeperBoard::MinesweeperBoard(int picked_width, int picked_height, GameMode picked_mode)
{
    width = picked_width;
    height = picked_height;
    moves = 0;
    revealed_fields = 0;
    mode = picked_mode;
    state = RUNNING;

    int mines_amount = 0;

    empty_board();

    switch(mode)
    {
        case EASY:
            mines_amount = ceil(width * height * 0.1);
            break;

        case NORMAL:
            mines_amount = ceil(width * height * 0.2);
            break;

        case HARD:
            mines_amount = ceil(width * height * 0.3);
            break;

        case DEBUG:
            for (int columns=0; columns<width; ++columns)
            {
                for(int rows=0; rows<height; ++rows)
                {
                    if(rows == 0)
                    {
                        data[rows][columns].hasMine = true;
                    }
                    if(rows == columns)
                    {
                        data[rows][columns].hasMine = true;
                    }
                    if((columns == 0) and rows % 2 == 0)
                    {
                        data[rows][columns].hasMine = true;
                    }
                }
            }
            break;
    }
    add_mines(mines_amount);
}

void MinesweeperBoard::debug_display()  const
{
    cout<<" ";
    for(int column_number=0; column_number<width; ++column_number)
    {
        cout<<setw(5)<<column_number;
    }
    for (int row=0; row<height; ++row)
    {
        cout<<endl<<setw(2)<<row<<" ";
        for(int column=0; column<width; ++column)
        {
            cout<<"[";
            if(data[row][column].hasMine)
                cout<<"M";
            else
                cout<<".";
            if(data[row][column].isRevealed)
                cout<<"o";
            else
                cout<<".";
            if(data[row][column].hasFlag)
                cout<<"f]";
            else
                cout<<".]";
        }
    }
    cout<<endl<<endl;
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

int MinesweeperBoard::getMineCount() const
{
    int counter = 0;
    for (int row=0; row<height; ++row)
    {
        for(int column=0; column<width; ++column)
        {
            if(data[row][column].hasMine)
            {
                counter++;
            }
        }
    }
    return counter;
}

int MinesweeperBoard::countMines(int row, int col) const
{
    if(!(is_on_board(row, col)))
    {
        return -1;
    }
    if(data[row][col].isRevealed == false)
    {
        return -1;
    }

    int counter = 0;
    for(int i=-1; i<=1; ++i)
    {
        for(int j=-1; j<=1; ++j)
        {
            counter += hasMine(row+i, col+j);
        }
    }
    counter = counter - data[row][col].hasMine;
    return counter;

}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if(!(is_on_board(row, col)))
    {
        return false;
    }

    return data[row][col].hasFlag;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if(!(is_on_board(row, col)) or (data[row][col].isRevealed))
    {
        return;
    }

    data[row][col].hasFlag = !(data[row][col].hasFlag);
}

void MinesweeperBoard::revealField(int row, int col)
{
    if(!(is_on_board(row, col)))
    {
        return;
    }

    if((data[row][col].hasFlag) or (data[row][col].isRevealed))
    {
        return;
    }

    if(state != RUNNING)
    {
        return;
    }

    data[row][col].isRevealed = true;

    if((data[row][col].hasMine) and (moves == 0))
    {
        add_mines(1);
        data[row][col].hasMine = false;
    }

    if((data[row][col].hasMine) and (moves > 0))
    {
        state = FINISHED_LOSS;
    }

    if(data[row][col].hasMine == 0)
    {
        revealed_fields++;
        adjust_board(row, col);
    }

    if((width * height) - revealed_fields == getMineCount())
    {
        state = FINISHED_WIN;
    }

    moves++;
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if(!(is_on_board(row, col)))
    {
        return false;
    }
    if(data[row][col].isRevealed)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if(!(is_on_board(row, col)))
    {
        return '#';
    }

    if((data[row][col].hasFlag) and (data[row][col].isRevealed == false))
    {
        return 'F';
    }

    if((data[row][col].hasMine))
    {
        return 'm';
    }

    if((data[row][col].hasFlag == false) and (data[row][col].isRevealed == false))
    {
        return '_';
    }

    if((data[row][col].hasMine) and (data[row][col].isRevealed))
    {
        return 'x';
    }

    if((countMines(row, col) == 0) and (data[row][col].isRevealed))
    {
        return ' ';
    }

    if((countMines(row, col) != 0) and (data[row][col].isRevealed))
    {
        char character = static_cast<char>(countMines(row, col) + '0');
        return character;
    }

    return ' ';
}

GameState MinesweeperBoard::getGameState() const
{
    return state;
}

void MinesweeperBoard::add_mines(int mines_amount)
{
    int rand_column, rand_row;
    int counter = 0;

    while(counter < mines_amount)
    {
        rand_row = rand() % height;
        rand_column = rand() % width;
        if(data[rand_row][rand_column].hasMine)
        {
            continue;
        }
        else
        {
            data[rand_row][rand_column].hasMine = true;
            counter++;
        }
    }
}

bool MinesweeperBoard::is_on_board(int row, int col) const
{
    if((row<0 or row>=height) or (col<0 || col>=width))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void MinesweeperBoard::adjust_board(int row, int col)
{
    if(!(is_on_board(row, col)))
    {
        return;
    }

    if(countMines(row, col) == 0)
    {
        for(int i=-1; i<=1; ++i)
        {
            for(int j=-1; j<=1; ++j)
            {
                if(is_on_board(row+i, col+j) and !(data[row+i][col+j].isRevealed))
                {
                    revealed_fields++;
                    data[row+i][col+j].isRevealed = true;
                    adjust_board(row+i, col+j);
                }
            }
        }
    }
}

void MinesweeperBoard::empty_board()
{
    for (int column=0; column<width; ++column)
    {
        for(int row=0; row<height; ++row)
        {
            data[row][column].hasMine = false;
            data[row][column].hasFlag = false;
            data[row][column].isRevealed = false;
        }
    }
}

bool MinesweeperBoard::hasMine(int row, int col) const
{
    if(!(is_on_board(row, col)))
    {
        return false;
    }

    return data[row][col].hasMine;
}