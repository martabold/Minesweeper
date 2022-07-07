#pragma once
#include "MinesweeperBoard.hpp"


class MSBoardTextView
{
    MinesweeperBoard &board;

    public:
    MSBoardTextView(MinesweeperBoard &board);
    void display();
    void win_or_loss();
    void main_menu();
};