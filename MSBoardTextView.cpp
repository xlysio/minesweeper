#include <iostream>
#include <iomanip>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

using namespace std;

MSBoardTextView::MSBoardTextView(MinesweeperBoard &picked_board) : board(picked_board)
{

}

void MSBoardTextView::display()
{
    cout<<"  ";
    for(int column_number=0 ; column_number<board.getBoardWidth(); column_number++)
    {
        cout<<setw(4)<<column_number;
    }
    for (int row=0; row<board.getBoardHeight(); ++row)
    {
        cout<<endl<<setw(2)<<row<<"  ";
        for(int column=0; column<board.getBoardWidth(); ++column)
        {
            cout<<"[";
            if(board.isRevealed(row, column))
            {
                cout<<board.countMines(row, column)<<"] ";
            }
            else if(board.hasFlag(row, column))
            {
                cout<<"f] ";
            }
            else
            {
                cout<<".] ";
            }
        }
    }
    cout<<endl<<endl;
}