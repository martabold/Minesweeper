#include "MSTextController.hpp"
#include <iostream>

MSTextController::MSTextController(MinesweeperBoard &board, MSBoardTextView &view)
: board(board), view(view)
{

}

void MSTextController::play()
{
    while (board.getGameState() == GameState::RUNNING)
    {
        system("clear");
        view.display();
        view.main_menu();
    }

    system("clear");
    view.display();
    view.win_or_loss();
}