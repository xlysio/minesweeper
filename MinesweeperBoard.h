#include <iostream>
#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard
{
    Field data[100][100];
    int width;
    int height;
    int moves;
    int revealed_fields;
    GameMode mode;
    GameState state;
    bool is_on_board(int row, int col) const;
    void add_mines(int mines_amount);
    void adjust_board(int row, int col);
    void empty_board();
    bool hasMine(int row, int col) const;

public:
    MinesweeperBoard();
    MinesweeperBoard(int picked_width, int picked_height, GameMode picked_mode);
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int row, int col) const;
    bool hasFlag(int row, int col) const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
    bool isRevealed(int row, int col) const;
    char getFieldInfo(int row, int col) const;
    GameState getGameState() const;
    void debug_display() const;
};

#endif //LAB2_MINESWEEPERBOARD_H