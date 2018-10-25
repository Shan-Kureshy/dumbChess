//
// Created by shan on 3/14/18.
//

#ifndef CHESS2_GAMEFUNCTIONS_H
#define CHESS2_GAMEFUNCTIONS_H


#define boardSize 8

void printBoard(int board[boardSize][boardSize]);
void runGame(int board[boardSize][boardSize]);

typedef struct coords{
    int xStart, yStart, xEnd, yEnd;
}coords;

coords translate(char coordString[5]);


#endif //CHESS2_GAMEFUNCTIONS_H