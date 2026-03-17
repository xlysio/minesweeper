#include <iostream>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#ifndef LAB2_MSTEXTCONTROLLER_H
#define LAB2_MSTEXTCONTROLLER_H


class MSTextController
{
    MinesweeperBoard &board;
    MSBoardTextView &view;

public:
    MSTextController(MinesweeperBoard &picked_board, MSBoardTextView &picked_view);
    void play();
};


#endif //LAB2_MSTEXTCONTROLLER_H