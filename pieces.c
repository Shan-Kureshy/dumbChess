//
// Created by shan on 3/14/18.
//
#include <stdlib.h>
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

int sameSigns(int a, int b){
    if((a>0 && b>0) || (a<0 && b<0))
        return 1;
    return 0;
}

int diffSigns(int a, int b){
    if((a>0 && b<0) || (a<0 && b>0))
        return 1;
    return 0;

}

int isEmpty(int board[boardSize][boardSize], int x, int y){
    if(board[y][x] == 0)
        return 1;
    return 0;
}

int correctTurn(int board[boardSize][boardSize],coords move, int turns){

    if(board[move.yStart][move.xStart] > 0 && (turns & 1))
        return 1;
    else if(board[move.yStart][move.xStart] < 0 && !(turns & 1))
        return 1;
    return 0;

}


int wPawnCheck(int board[boardSize][boardSize], coords move){
    if(isEmpty(board, move.xEnd, move.yEnd)){
        if(move.xEnd - move.xStart == 0 /*if x position isnt changing */
           && ((move.yStart == 6 && move.yStart -  move.yEnd <= 2 && isEmpty(board, move.xStart, move.yStart -1))/*can moveCoords 2 if in starting position, wont jump over piece */
               ||move.yStart - move.yEnd == 1 )){/* moveCoords 1 otherwise*/
            return 1;

        }

    }
    else if(diffSigns(board[move.yEnd][move.xEnd], board[move.yStart][move.xStart])){ /* if space is occupied by enemy piece*/
        if(move.yStart - move.yEnd ==1 && abs(move.xEnd - move.xStart) == 1)/* if movement is diagonal */
            return 1;
    }
    return 0;

}

int bPawnCheck(int board[boardSize][boardSize], coords move){
    if(isEmpty(board, move.xEnd, move.yEnd)){
        if(move.xEnd - move.xStart == 0 /*if x position isnt changing */
           && ((move.yStart == 1 && move.yEnd -  move.yStart <= 2 && isEmpty(board, move.xStart, move.yStart+1))/*can moveCoords 2 if in starting position, wont jump over piece */
               ||move.yEnd - move.yStart == 1 )){/* moveCoords 1 elsewise*/
            return 1;

        }

    }
    else if(diffSigns(board[move.yEnd][move.xEnd], board[move.yStart][move.xStart])){ /* if space is occupied by enemy piece*/
        if(move.yEnd - move.yStart ==1 && move.xEnd - move.xStart == 1)/* if movement is diagonal */
            return 1;
    }
    return 0;
}

int rookCheck(int board[boardSize][boardSize], coords move){

    if(move.xStart == move.xEnd){ //if start and end are on same x axis

        if(move.yStart > move.yEnd){ //if start is below end
            for(int i = move.yEnd+1;i < move.yStart; i++){
                if(!isEmpty(board, move.xStart, i)) //check collision for all spaces between start and end
                    return 0;
            }
        }

        else //if start is above end
            for(int i = move.yStart+1;i < move.yEnd; i++){
                if(!isEmpty(board, move.xStart, i))  //check collision for all spaces between start and end
                    return 0;
            }
    }

    else if (move.yStart == move.yEnd){ //if start and end are on same y axis

        if(move.xStart > move.xEnd){ //if start is below end
            for(int i = move.xEnd+1;i < move.xStart; i++){
                if(!isEmpty(board, i, move.yStart)) //check collision for all spaces between start and end
                    return 0;
            }
        }

        else //if start is above end
            for(int i = move.xStart+1;i < move.xEnd; i++){
                if(!isEmpty(board, i, move.yStart)) //check collision for all spaces between start and end
                    return 0;
            }
    }
    else return 0;

}

int bishopCheck(int board[boardSize][boardSize], coords move){

    if(abs(move.xEnd-move.xStart) == abs(move.yEnd-move.yStart)) { // if end point is diagonal to start point

        if (move.xEnd > move.xStart) { //if end is to right of start
            if (move.yEnd > move.yStart) { //if end is below start
                for (int i = 1; i < move.xEnd-move.xStart; i++) {
                    if (!isEmpty(board, move.xStart + i, move.yStart + i)) //check collision for spaces in between start and end
                        return 0;
                }
                return 1;
            }

            else{  //if end is above start
                for (int i = 1; i < move.xEnd-move.xStart; i++) {
                    if (!isEmpty(board, move.xStart + i, move.yStart - i)) //check collision for spaces in between start and end
                        return 0;
                }
                return 1;
            }
        }

        else{//if end is to the left of start
            if (move.yEnd > move.yStart) { //if end is below start
                for (int i = 1; i < move.xStart-move.xEnd; i++) {
                    if (!isEmpty(board, move.xStart - i, move.yStart + i)) //check collision for spaces in between start and end
                        return 0;
                }
                return 1;
            }

            else{ //if end is above start
                for (int i = 1; i < move.xStart-move.xEnd; i++) {
                    if (!isEmpty(board, move.xStart - i, move.yStart - i)) //check collision for spaces in between start and end
                        return 0;
                }
                return 1;
            }
        }

    }
    return 0;
}

int knightCheck(int board[boardSize][boardSize], coords move){
    if(((abs(move.xStart - move.xEnd) == 2 && abs(move.yStart - move.yEnd) == 1) //checks if start is 2 blocks away from end in one direction and 1 block from other direction
           || abs(move.xStart - move.xEnd) == 1 && abs(move.yStart - move.yEnd) == 2))
                return 1;
    return 0;

}

int kingCheck(int board[boardSize][boardSize], coords move){ //TODO: add castling
    if((abs(move.xStart-move.xEnd)<=1 && abs(move.yStart-move.yEnd)<=1)) // if end point is one tile away from start point
        return 1;

    else if(board[move.yStart][move.xStart] == 6 && board[7][7] == 2){
        if(board[7][5] == 0){
            board[7][5] = 2;
            board[7][7] = 0;
            return 1;
        }
    }
    
    else if(board[move.yStart][move.xStart] == -6 && board[0][7] == -2){
        if(board[0][5] == 0){
            board[0][5] = -2;
            board[0][7] = 0;
            return 1;

        }
    }

    return 0;
}

int isValid(int board[boardSize][boardSize], coords move){

    if(!(move.xStart == move.xEnd && move.yStart == move.yEnd) /*makes sure piece is moving and isn't capturing friendly piece */
       && !sameSigns(board[move.yStart][move.xStart], board[move.yEnd][move.xEnd]))
        switch(board[move.yStart][move.xStart]){

            case wPawn:
                return wPawnCheck(board, move);

            case bPawn:
                return bPawnCheck(board, move);

            case wRook:
            case bRook:
                return rookCheck(board, move);

            case wKnight:
            case bKnight:
                return knightCheck(board, move);


            case wBishop:
            case bBishop:
                return bishopCheck(board, move);


            case wQueen:
            case bQueen:
                return (bishopCheck(board, move) || rookCheck(board, move)); //since queen can moveCoords like bishop or rook, check if queen's moveCoords is bishop-like or rook -like

            case wKing:
            case bKing:
                return kingCheck(board, move);

            default:
                return 0;
    }
    else return 0;
}

int move(int board[boardSize][boardSize], coords move) { //moves piece from start to end location

    if (isValid(board, move)) {
        board[move.yEnd][move.xEnd] = board[move.yStart][move.xStart];
        board[move.yStart][move.xStart] = 0;
        return 1;

    }
    else
        return 0;
}
