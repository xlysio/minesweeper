#include <iostream>
#include "MSTextController.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

using namespace std;

MSTextController::MSTextController(MinesweeperBoard &picked_board, MSBoardTextView &picked_view): board(picked_board), view(picked_view)
{

}

void MSTextController::play()
{
    int option, row, column;
    cout<<"Let's play minesweeper."<<endl<<"In order to win you have to disarm the entire board."<<endl;
    cout<<"There are "<<board.getMineCount()<<" mines on the board."<<endl;

    while(board.getGameState() == RUNNING)
    {
        view.display();
        cout<<"Pick your move by pressing the correct key."<<endl;
        cout<<"1. Reveal field.  "<<"  2. Toggle flag."<<endl;
        cin>>option;

        switch(option)
        {
            case 1:
            {
                cout<<"Type the coordinates you want to reveal (row, column):"<<endl;
                cin>>row>>column;
                board.revealField(row, column);
                break;
            }
            case 2:
            {
                cout<<"Type the coordinates you want to toggle flag on (row, column):"<<endl;
                cin>>row>>column;
                board.toggleFlag(row, column);
                break;
            }
            default:
            {
                cout<<"Pick a valid option"<<endl;
                break;
            }
        }
    }

    cout<<endl;

    switch(board.getGameState())
    {

        case 0:
        {
            cout<<"The game is still running."<<endl;
            break;
        }
        case 1:
        {
            cout<<"You won."<<endl;
            break;
        }
        case 2:
        {
            cout<<"You lost."<<endl;
            break;
        }
    }
}