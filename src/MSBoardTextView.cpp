#include "MSBoardTextView.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

MSBoardTextView::MSBoardTextView(MinesweeperBoard &board)
: board(board)
{

}


void MSBoardTextView::display()
{
    for(int row = 0; row < board.getBoardHeight(); row++)
    {
        for(int col = 0; col < board.getBoardWidth(); col++)
        {
            std::cout << "[";
            std::cout << board.getFieldInfo(row, col);
            std::cout << "]";
        }
        std::cout<<std::endl;
    }
}

void MSBoardTextView::win_or_loss()
{
    if(board.getGameState() == GameState::FINISHED_WIN)
    {
        std::string win = "CONGRATS! YOU WON THE GAME!";
        int size = win.size() + 5;
        std::string frame (size, '*');
        std::string whole = frame + "\n";
        whole += win + "\n";
        whole += frame;
        std::cout<< whole << std::endl;
    }
    if(board.getGameState() == GameState::FINISHED_LOSS)
    {
        std::string win = "SORRY! :( YOU LOST!";
        int size = win.size() + 5;
        std::string frame (size, '*');
        std::string whole = frame + "\n";
        whole += win + "\n";
        whole += frame;
        std::cout<< whole << std::endl;
    }
}

void MSBoardTextView::main_menu()
{
    int choice = 0;
    int row = 0;
    int column = 0;

    std::string win = "WELCOME TO MINESWEEPER!";
    int size = win.size() + 5;
    std::string frame (size, '*');
    std::string whole = frame + "\n";
    whole += win + "\n";
    whole += frame;
    std::cout<< whole << std::endl;

    std::cout<<"The current game consists of a board measuring 10 squares high and 20 squares wide."<<std::endl;
    std::cout<<"You can make the following moves: "<<std::endl;
    std::cout<<"1. Reveal a field"<<std::endl;
    std::cout<<"2. Mark the field as 'flagged' or unflag the field"<<std::endl;
    std::cout<<"3. Leave the game"<<std::endl;
    std::cout<<"Choose your move: ";
    std::cin>>choice;
    

    switch(choice)
    {
        case 1:
        {
            std::cout<<"\nSelect a row of a field which you'd like to reveal: ";
        std::cin>>row;
        std::cout<<std::endl;
        std::cout<<"Select a column of a field which you'd like to reveal: ";
        std::cin>>column;
        board.revealField((row-1), (column-1));
        break;
        }

        case 2:
        {
            std::cout<<"\nSelect a row of a field in which you'd like to place a flag: ";
        std::cin>>row;
        std::cout<<std::endl;
        std::cout<<"Select a column of a field in which you'd like to place a flag: ";
        std::cin>>column;
        board.toggleFlag((row-1), (column-1));
        break;
        }

        case 3:
        {
            
            exit(0);
        }
        default:
        {
            std::cout<<"You've selected an incorrect character!"<<std::endl;
            break;
        }

    
    }

}
