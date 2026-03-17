#include <iostream>
#include "MSTextController.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

int main()
{
    srand(time(NULL));

    MinesweeperBoard board(10, 8, DEBUG);
    MSBoardTextView view(board);
    MSTextController ctrl(board, view);
    std::cout<<board.getFieldInfo(0,0)<<std::endl;
    board.debug_display();
    ctrl.play();
    board.debug_display();
    return 0;
}