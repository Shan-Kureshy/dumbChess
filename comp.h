//
// Created by shan on 3/22/18.
//
#include "gameFunctions.h"

#define boardSize 8
#define wPawn 1
#define wRook 2
#define wKnight 3
#define wBishop 4
#define wQueen 5
#define wKing 6
#define bPawn (-1)
#define bRook (-2)
#define bKnight (-3)
#define bBishop (-4)
#define bQueen (-5)
#define bKing (-6)

#ifndef CHESS2_COMP_H
#define CHESS2_COMP_H
typedef struct compCoords{
    coords moveCoords;
    int points;
}compCoords;

compCoords bestMove(int board[boardSize][boardSize], compCoords compMoves[], int size);
coords generateMove(int board[boardSize][boardSize]);
int evaluateBoard(int board[boardSize][boardSize], coords move);

int predictMove(int board[boardSize][boardSize], coords move);

#endif //CHESS2_COMP_H
