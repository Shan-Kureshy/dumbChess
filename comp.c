//
// Created by shan on 3/22/18.
//

#include <time.h>
#include <stdlib.h>
#include "gameFunctions.h"
#include "comp.h"
#include "pieces.h"

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

int evaluateBoard(int board[boardSize][boardSize], coords move){
    // piece tables from https://chessprogramming.wikispaces.com/Simplified+evaluation+function
    // used to evaluate if a move gives a piece better strategic positioning
    //points are added or subtracted to a move if it captures a piece or moves to a specific space on the board
    int bPawnBoard[boardSize][boardSize] = {
            { 0,  0,  0,  0,  0,  0,  0,  0},
            {5, 10, 10,-20,-20, 10, 10,  5},
            {5, -5,-10,  0,  0,-10, -5,  5},
            {0,  0,  0, 20, 20,  0,  0,  0},
            {5,  5, 10, 25, 25, 10,  5,  5},
            {10, 10, 20, 30, 30, 20, 10, 10},
            {50, 50, 50, 50, 50, 50, 50, 50},
            {0,  0,  0,  0,  0,  0,  0,  0}
    };

    int wPawnBoard[boardSize][boardSize] = {
            {0,  0,  0,  0,  0,  0,  0,  0},
            {50, 50, 50, 50, 50, 50, 50, 50},
            {10, 10, 20, 30, 30, 20, 10, 10},
            {5,  5, 10, 25, 25, 10,  5,  5},
            {0,  0,  0, 20, 20,  0,  0,  0},
            {5, -5,-10,  0,  0,-10, -5,  5},
            {5, 10, 10,-20,-20, 10, 10,  5},
            {0,  0,  0,  0,  0,  0,  0,  0}
    };

    int bKnightBoard[boardSize][boardSize] = {
            {-50,-40,-30,-30,-30,-30,-40,-50},
            {-40,-20,  0,  5,  5,  0,-20,-40},
            {-30,  5, 10, 15, 15, 10,  5,-30},
            {-30,  0, 15, 20, 20, 15,  0,-30},
            {-30,  5, 15, 20, 20, 15,  5,-30},
            {-30,  0, 10, 15, 15, 10,  0,-30},
            {-40,-20,  0,  0,  0,  0,-20,-40},
            {-50,-40,-30,-30,-30,-30,-40,-50}
    };

    int wKnightBoard[boardSize][boardSize] = {
            {-50,-40,-30,-30,-30,-30,-40,-50},
            {-40,-20,  0,  0,  0,  0,-20,-40},
            {-30,  0, 10, 15, 15, 10,  0,-30},
            {-30,  5, 15, 20, 20, 15,  5,-30},
            {-30,  0, 15, 20, 20, 15,  0,-30},
            {-30,  5, 10, 15, 15, 10,  5,-30},
            {-40,-20,  0,  5,  5,  0,-20,-40},
            {-50,-40,-30,-30,-30,-30,-40,-50}
    };

    int bBishopBoard[boardSize][boardSize] = {
            {-20,-10,-10,-10,-10,-10,-10,-20},
            {-10,  5,  0,  0,  0,  0,  5,-10},
            {-10, 10, 10, 10, 10, 10, 10,-10},
            {-10,  0, 10, 10, 10, 10,  0,-10},
            {-10,  5,  5, 10, 10,  5,  5,-10},
            {-10,  0,  5, 10, 10,  5,  0,-10},
            {-10,  0,  0,  0,  0,  0,  0,-10},
            {-20,-10,-10,-10,-10,-10,-10,-20}
    };

    int wBishopBoard[boardSize][boardSize] = {
            {-20,-10,-10,-10,-10,-10,-10,-20},
            {-10,  0,  0,  0,  0,  0,  0,-10},
            {-10,  0,  5, 10, 10,  5,  0,-10},
            {-10,  5,  5, 10, 10,  5,  5,-10},
            {-10,  0, 10, 10, 10, 10,  0,-10},
            {-10, 10, 10, 10, 10, 10, 10,-10},
            {-10,  5,  0,  0,  0,  0,  5,-10},
            {-20,-10,-10,-10,-10,-10,-10,-20}
    };

    int bRookBoard[boardSize][boardSize] = {
            { 0,  0,  0,  5,  5,  0,  0,  0},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            { 5, 10, 10, 10, 10, 10, 10,  5},
            { 0,  0,  0,  0,  0,  0,  0,  0}
    };

    int wRookBoard[boardSize][boardSize] = {
            { 0,  0,  0,  0,  0,  0,  0,  0},
            { 5, 10, 10, 10, 10, 10, 10,  5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            { 0,  0,  0,  5,  5,  0,  0,  0}
    };

    int bQueenBoard[boardSize][boardSize] = {
            {-20,-10,-10, -5, -5,-10,-10,-20},
            {-10,  0,  5,  0,  0,  0,  0,-10},
            {-10,  5,  5,  5,  5,  5,  0,-10},
            { -5,  0,  5,  5,  5,  5,  0, -5},
            {  0,  0,  5,  5,  5,  5,  0, -5},
            {-10,  0,  5,  5,  5,  5,  0,-10},
            {-10,  0,  0,  0,  0,  0,  0,-10},
            {-20,-10,-10, -5, -5,-10,-10,-20}
    };

    int wQueenBoard[boardSize][boardSize] = {
            {-20,-10,-10, -5, -5,-10,-10,-20},
            {-10,  0,  0,  0,  0,  0,  0,-10},
            {-10,  0,  5,  5,  5,  5,  0,-10},
            {-5,  0,  5,  5,  5,  5,  0, -5},
            {0,  0,  5,  5,  5,  5,  0, -5},
            {-10,  5,  5,  5,  5,  5,  0,-10},
            {-10,  0,  5,  0,  0,  0,  0,-10},
            {-20,-10,-10, -5, -5,-10,-10,-20}
    };

    int bKingBoard[boardSize][boardSize] = {
            { 20, 30, 10,  0,  0, 10, 30, 20},
            {20, 20,  0,  0,  0,  0, 20, 20},
            {-10,-20,-20,-20,-20,-20,-20,-10},
            {-20,-30,-30,-40,-40,-30,-30,-20},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30}
    };

    int wKingBoard[boardSize][boardSize] = {
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-20,-30,-30,-40,-40,-30,-30,-20},
            {-10,-20,-20,-20,-20,-20,-20,-10},
            {20, 20,  0,  0,  0,  0, 20, 20},
            {20, 30, 10,  0,  0, 10, 30, 20}
    };


    int movePoints = 0;

    switch(board[move.yStart][move.xStart]){ // evaluates how well piece is positioned on board by adding the value in the above matrices to movePoints
        case bPawn:
            movePoints += bPawnBoard[move.yEnd][move.xEnd];
            break;
        case wPawn:
            movePoints += wPawnBoard[move.yEnd][move.xEnd];
            break;

        case bKnight:
            movePoints += bKnightBoard[move.yEnd][move.xEnd];
            break;
        case wKnight:
            movePoints += wKnightBoard[move.yEnd][move.xEnd];
            break;

        case bBishop:
            movePoints += bBishopBoard[move.yEnd][move.xEnd];
            break;
        case wBishop:
            movePoints += wBishopBoard[move.yEnd][move.xEnd];
            break;

        case bRook:
            movePoints += bRookBoard[move.yEnd][move.xEnd];
            break;
        case wRook:
            movePoints += wRookBoard[move.yEnd][move.xEnd];
            break;

        case bQueen:
            movePoints += bQueenBoard[move.yEnd][move.xEnd];
            break;
        case wQueen:
            movePoints += wQueenBoard[move.yEnd][move.xEnd];
            break;

        case bKing:
            movePoints +=bKingBoard[move.yEnd][move.xEnd];
            break;
        case wKing:
            movePoints +=wKingBoard[move.yEnd][move.xEnd];
            break;

        default: break;
    }

    switch(board[move.yEnd][move.xEnd]){ //evaluates possible captures based on point values assigned to different types of pieces
        case wPawn:
        case bPawn:
            movePoints += 100;
            break;

        case wKnight:
        case bKnight:
            movePoints += 320;
            break;

        case wBishop:
        case bBishop:
            movePoints += 330;
            break;

        case wRook:
        case bRook:
            movePoints += 500;
            break;

        case wQueen:
        case bQueen:
            movePoints += 900;
            break;

        case wKing:
        case bKing:
            movePoints +=20000;
            break;

        default: break;
    }
    return movePoints;
}

int predictMove(int board[boardSize][boardSize], coords move){
    int boardCopy[boardSize][boardSize];

    for(int row = 0; row < boardSize; row++) //Make copy of the board, so original board isnt modified
        for(int col = 0; col < boardSize; col++)
            boardCopy[row][col] = board[row][col];

    boardCopy[move.yEnd][move.xEnd] = boardCopy[move.yStart][move.xStart];
    boardCopy[move.yStart][move.xStart] = 0;

    compCoords possibleMoves[152];

    int moveCount = 0;
    for(int rowStart = 0; rowStart < 8; rowStart++){
        for(int colStart = 0; colStart < 8; colStart++){ //searches entire board for black pieces

            if(boardCopy[rowStart][colStart] > 0) { //if piece is white

                for (int rowEnd = 0; rowEnd < 8; rowEnd++){ //searches board for possible moves for current black piece
                    for (int colEnd = 0; colEnd < 8; colEnd++){
                        compCoords tempMove;
                        tempMove.moveCoords.xStart = colStart;
                        tempMove.moveCoords.yStart = rowStart;
                        tempMove.moveCoords.xEnd = colEnd;
                        tempMove.moveCoords.yEnd = rowEnd;

                        if(isValid(boardCopy, tempMove.moveCoords)){ //add moveCoords to array is moveCoords is valid
                            tempMove.points = evaluateBoard(boardCopy, tempMove.moveCoords);
                            possibleMoves[moveCount] = tempMove;
                            moveCount++;
                        }
                    }
                }
            }
        }
    }

    compCoords best = possibleMoves[0];
    for(int i = 0; i <moveCount; i++){
        if(possibleMoves[i].points > best.points){
            best = possibleMoves[i];

        }
    }

    return best.points;

}

//evaluates score from all possible moves according to predicted outcomes from one move ahead
compCoords bestMove(int board[boardSize][boardSize], compCoords compMoves[], int size){
    compCoords best = compMoves[0];

    best.points -= predictMove(board, best.moveCoords);


    for(int i = 1; i < size; i++){
        compMoves[i].points -= predictMove(board, compMoves[i].moveCoords);
        if(compMoves[i].points > best.points){
            best = compMoves[i];

        }
    }

    return best;
}


coords generateMove(int board[boardSize][boardSize]){

    compCoords possibleMoves[152]; //At any given time, there is a max of 152 possible moves on a chess board
    int moveCount = 0;
    //time_t currentTime;
    //srand((unsigned) time(&currentTime)); //used for choosing a random moveCoords

    for(int rowStart = 0; rowStart < 8; rowStart++){
        for(int colStart = 0; colStart < 8; colStart++){ //searches entire board for black pieces

            if(board[rowStart][colStart] < 0) { //if piece is black

                for (int rowEnd = 0; rowEnd < 8; rowEnd++){ //searches board for possible moves for current black piece
                    for (int colEnd = 0; colEnd < 8; colEnd++){
                        compCoords tempMove;
                        tempMove.moveCoords.xStart = colStart;
                        tempMove.moveCoords.yStart = rowStart;
                        tempMove.moveCoords.xEnd = colEnd;
                        tempMove.moveCoords.yEnd = rowEnd;

                        if(isValid(board, tempMove.moveCoords)){ //add moveCoords to array is moveCoords is valid
                            tempMove.points = evaluateBoard(board, tempMove.moveCoords);
                            possibleMoves[moveCount] = tempMove;
                            moveCount++;
                        }
                    }
                }
            }
        }
    }

    //return possibleMoves[rand() % moveCount].moveCoords; //returns random moveCoords out of array
    return bestMove(board, possibleMoves, moveCount).moveCoords;
}