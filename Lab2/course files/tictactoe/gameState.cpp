//
//  gameState.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.

#include "tictactoe.h"
#include "gameState.h"

int gameState::get_clickedRow()
{
    return clickedRow;
}

int gameState::get_clickedColumn()
{
    return clickedColumn;
}

void gameState::set_clickedRow(int value)
{
    if (value < boardSize && value >= 0)
    {
        clickedRow = value;
    }
}

void gameState::set_clickedColumn(int value)
{
    if (value < boardSize && value >= 0)
    {
        clickedColumn = value;
    }
}

bool gameState::get_moveValid()
{
    return moveValid;
}

void gameState::set_moveValid(bool value)
{
    moveValid = value;
}

bool gameState::get_gameOver()
{
    return gameOver;
}

void gameState::set_gameOver(bool value)
{
    gameOver = value;
}

int gameState::get_winCode()
{
    return winCode;
}

void gameState::set_winCode(int value)
{
    winCode = (value < 9 && value > -1) ? value : winCode;
}

bool gameState::get_turn()
{
    return turn;
}

void gameState::set_turn(bool value)
{
    turn = value;
}

int gameState::get_gameBoard(int row, int col)
{
    return gameBoard[row][col];
} 

#include <iostream>
void gameState::set_gameBoard(int row, int col, int value)
{
    //std::cout << "changing";
    //if (gameBoard[row][col] == Empty)
    //{
    //    std::cout << "Not Now";
        gameBoard[row][col] = value;
    //}
    //std::cout << "\n";
}
