//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h"
#include "gameState.h"

//#include <iostream>
bool first = true;

void playMove(gameState& game_state) {
    //Initializing the Game Board on first run
    if(first)
    for (int r = 0 ; r < boardSize ; r++)
    {
	for(int c = 0 ; c < boardSize; c++)
	{
	    game_state.set_gameBoard(r,c,Empty);
	}
    }
    first = false;
    // Getting Row and Column set by Display Server
    int row = game_state.get_clickedRow();
    int col = game_state.get_clickedColumn();
    // Getting Player acording to turn
    int player = game_state.get_turn()? X:O;
    int winCode = 0;
    int counter = 0;
    // Setting WinCode as zero in the beginning
    game_state.set_winCode(winCode);
    if(game_state.get_gameBoard(row,col) == Empty)
    {
        // Valid Move
        game_state.set_gameBoard(row,col, player);
        game_state.set_moveValid(true);
	game_state.set_turn(!game_state.get_turn());
    }
    else
    {
        // Invalid Move 
        game_state.set_moveValid(false);
        return ;
    }
    // Assume Game Over as true unless proven otherwise
    game_state.set_gameOver(true);
    for(int r = 0; r < boardSize; r++)
    {
        for(int c=0; c < boardSize; c++)
        {
            if(game_state.get_gameBoard(r,c) == Empty)
                game_state.set_gameOver(false);
        }
    }
    // Check For winner by counting number of X's or O's in line
    for(int r = 0; r < boardSize; r++)
    {
        counter = 0;
        for(int c=0; c < boardSize; c++)
        {
            if(game_state.get_gameBoard(r,c) != player)
            {
                break;
            }
            counter++;
        }
        if(counter == boardSize)
        {
            winCode = r+1;
            break;
        }
    }
    // If Wincode is not zero = > Game over
    if(winCode)
    {
        game_state.set_winCode(winCode);
        game_state.set_turn(!game_state.get_turn());
        game_state.set_gameOver(true);
	return;
    }
    for(int c = 0; c < boardSize; c++)
    {
        counter = 0;
        for(int r=0; r < boardSize; r++)
        {
            if(game_state.get_gameBoard(r,c) != player)
            {
                break;
            }
            counter++;
        }
        if(counter == boardSize)
        {
            winCode = c+4;
            break;
        }
    }
    if(winCode)
    {
        game_state.set_winCode(winCode);
        game_state.set_turn(!game_state.get_turn());
        game_state.set_gameOver(true);
	return;
    }
    counter = 0;
    for(int i=0 ; i < boardSize; i++)
    {
        if(game_state.get_gameBoard(i,i) != player)
        {
            break;
        }
        counter++;
    }
    if(counter==boardSize)
    {
        winCode = 7;
    }
    counter = 0;
    for(int i=0 ; i < boardSize; i++)
    {
        if(game_state.get_gameBoard(boardSize - i -1 ,i) != player)
        {
            break;
        }
        counter++;
    }
    if(counter==boardSize)
    {
    	winCode = 8;
    }
    if(winCode)
    {
        game_state.set_winCode(winCode);
        game_state.set_turn(!game_state.get_turn());
        game_state.set_gameOver(true);
	return;
    }
    // If not Exited yet, Game not over
    game_state.set_winCode(0);
}

