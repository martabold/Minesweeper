#pragma once
#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"

class MSTextController
{
  MinesweeperBoard &board;
  MSBoardTextView &view;

  public:
  MSTextController(MinesweeperBoard &board, MSBoardTextView &view);
  void play();

};