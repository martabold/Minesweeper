#include "MinesweeperBoard.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>


std::string debugDisplayField(const Field &f) //zawiera stringi z info o polu
{
    std::string result = "[";
    result += f.hasMine ? 'M' : '.';
    result += f.isRevealed ? 'o' : '.';
    result += f.hasFlag ? 'f' : '.';
    result += "]";
   
    return result;
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode)
    : width(width), 
    height(height),
    mode(mode),
    numberOfMines(static_cast<int>(mode) * width * height / 100), 
    board(height * width, Field{false, false, false}),
    state(GameState::RUNNING) // konstruktor MinesweeperBoard
{
    if (numberOfMines > 0)
    {
        int any_row;
        int any_col;

        std::random_device root;
        std::mt19937 whatever(root());
        std::uniform_int_distribution<> distrib_row(0, height - 1);
        std::uniform_int_distribution<> distrib_col(0, width - 1);

        for (int i = 0; i < numberOfMines; i++)
        {
            any_row = distrib_row(whatever);
            any_col = distrib_col(whatever);

            if (cartesianIntoElements(any_row, any_col).hasMine == false)
            {
                cartesianIntoElements(any_row, any_col) = {1, 0, 0};
            }
            else
            {
                i--;
            }
        }
    }
    else if (mode == GameMode::DEBUG)
    {
        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                if (row == col || row == 0 || (col == 0 && row % 2 == 0))
                {
                    cartesianIntoElements(row, col) = {1, 0, 0};
                }
            }
        }
    }
}

Field &MinesweeperBoard::cartesianIntoElements(int row, int column) //zamiana wspolrzednych kartezjanskich na indeks jakiegos elementu macierzy
{
    return board.at(row  + column * height);
}

const Field &MinesweeperBoard::cartesianIntoElements(int row, int column) const // to samo co wyzej ale dla funkcji const
{
    return board.at(row + column * height);
}

void MinesweeperBoard::debug_display() const //testowe wyswietlanie
{
    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            std::cout << debugDisplayField(cartesianIntoElements(row, column));
        }

        std::cout << std::endl;
    }
}

bool MinesweeperBoard::conditionOffTheBoard(int row, int col) const
{
    return ((row < 0 || row >= height) || (col < 0 ||  col >= width));
}

int MinesweeperBoard::getBoardWidth() const //zwraca szerokosc planszy
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const //zwraca wysokosc planszy
{
    return height;
}

int MinesweeperBoard::getMineCount() const 
{
    return numberOfMines;
}

int MinesweeperBoard::countMines(int row, int col) const
{
    int bomb_counter = 0;

    if (conditionOffTheBoard(row, col) || (board[row  + col * height].isRevealed == false))
    {
        return -1; 
    }
    else
    {
        
        for (int i = row - 1; i <= row + 1; ++i)
        {
            for (int j = col - 1; j <= col + 1; ++j)
            {
                {
                    if ((i != row || j != col) && ((i >= 0 && i <= height - 1) && (j >= 0 && j <= width - 1)))
                    {
                        if (board[i+height *j].hasMine == true)
                        {
                            bomb_counter++;
                        }
                    }
                }
            }
        }

        return bomb_counter;
    }
}

bool MinesweeperBoard::hasFlag(int row, int col) const //ma flage czy nie
{
    if(conditionOffTheBoard(row, col) || (cartesianIntoElements(col, row).hasFlag == false) || (cartesianIntoElements(col, row).isRevealed == true ))
    {
        return false;
    }
    return cartesianIntoElements(row, col).hasFlag;
}

void MinesweeperBoard::toggleFlag(int row, int col) //ustawia flage
{

    if(conditionOffTheBoard(row, col) || (cartesianIntoElements(row, col).isRevealed == true) || state == GameState::FINISHED_LOSS || state == GameState::FINISHED_WIN)
    {
        return;
    }
    
    
        if(cartesianIntoElements(row, col).hasFlag == false)
        {
            cartesianIntoElements(row, col).hasFlag = true;
            return;
        }

    cartesianIntoElements(row, col).hasFlag = false;

}

void MinesweeperBoard::revealField(int row, int col) //ukazuje pole
{
    int revealedFields = 0;

    if(conditionOffTheBoard(row, col) || (cartesianIntoElements(row, col).isRevealed == true) || (cartesianIntoElements(row, col).hasFlag == true) || state == GameState::FINISHED_LOSS || state == GameState::FINISHED_WIN)
    {
        return;
    }

        cartesianIntoElements(row, col).isRevealed = true;

        if(cartesianIntoElements(row, col).hasMine == true)
        {
            state = GameState::FINISHED_LOSS;
        }

        for(int row = 0; row < width; row++)
        {
            for(int col = 0; col < height; col++)
            {
                if((cartesianIntoElements(row, col).isRevealed == true) && (cartesianIntoElements(row, col).hasMine == false))
                {
                    revealedFields++;
                }
                if(revealedFields==(width*height) - getMineCount())
                {
                    state = GameState::FINISHED_WIN;
                }
            }

        }
}

bool MinesweeperBoard::isRevealed(int row, int col) const //czy jest odryte czy nie
{
    if((row >= 0 && row < height) && (col >= 0 &&  col < width))
    {
        if(cartesianIntoElements(row, col).isRevealed == true)
        {
            return true;
        }
    }
    
    return false;
}

GameState MinesweeperBoard::getGameState() const //zwraca 'stan' gry
{
    return state;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const 
{
    if(conditionOffTheBoard(row, col))
    {
        return '#';
    }
    if ((cartesianIntoElements(row, col).isRevealed == false) && (cartesianIntoElements(row, col).hasFlag == true))
    {
        return 'F';
    }
    if((cartesianIntoElements(row, col).isRevealed == false) && (cartesianIntoElements(row, col).hasFlag == false))
    {
        return '_';
    }
    if((cartesianIntoElements(row, col).isRevealed == true) && (cartesianIntoElements(row, col).hasMine == true))
    {
        return 'x';
    }
    if(countMines(row, col)==0)
    {
        return ' ';
    }

    else
    {
       return '0'+countMines(row, col); 
    }
    
}