#include "MinesweeperBoard.hpp"

#include "MSBoardTextView.hpp"
#include "MSTextController.hpp"
#include <iostream>

int main()
{
    /*MinesweeperBoard board(10,10, GameMode::EASY);
    //board.debug_display();
    MSBoardTextView view{board};
    //view.display();
    //board.revealField(0,5); 
    board.toggleFlag(0,0);
    board.revealField(6,8);
    //board.debug_display();
    
    view.display();*/



    MinesweeperBoard board{20, 10, GameMode::EASY};
    MSBoardTextView view{board};
    MSTextController ctrl{board, view};
    ctrl.play();

    return 0;
}