#include <iostream>
#include "MinesweeperBoard.h"
#ifndef LAB2_MSBOARDTEXTVIEW_H
#define LAB2_MSBOARDTEXTVIEW_H


class MSBoardTextView
{
    MinesweeperBoard &board;

public:
    MSBoardTextView(MinesweeperBoard &picked_board);
    void display();
};


#endif //LAB2_MSBOARDTEXTVIEW_H