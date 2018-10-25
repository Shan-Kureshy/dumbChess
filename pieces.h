//
// Created by shan on 3/14/18.
//

#include <stdio.h>
#include "gameFunctions.h"

#ifndef CHESS2_PIECES_H
#define CHESS2_PIECES_H

int sameSigns(int a, int b); //checks if two pieces are the same color
int diffSigns(int a, int b); //checks if two pieces are different colors
int isEmpty(int board[boardSize][boardSize], int x, int y); //checks if a space on a board is empty
int correctTurn(int board[boardSize][boardSize], coords move, int turns); //checks if player is moving a piece they are allowed to moveCoords

int wPawnCheck(int board[boardSize][boardSize], coords move); //checks validity of different pieces
int bPawnCheck(int board[boardSize][boardSize], coords move);
int rookCheck(int board[boardSize][boardSize], coords move);
int bishopCheck(int board[boardSize][boardSize], coords move);
int kingCheck(int board[boardSize][boardSize], coords move);
int knightCheck(int board[boardSize][boardSize], coords move);

int isValid(int board[boardSize][boardSize], coords move); //checks if a moveCoords is valid
int move(int board[boardSize][boardSize], coords move); //moves pieces if valid



#endif //CHESS2_PIECES_H

