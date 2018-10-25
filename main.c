
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

/*TODO: rules to implement
 * castling
 * en passant
 * pawn becomes queen on opposite side
 * check/checkmate
 *
 * TODO: additional features
 * captured pieces log
 * undo previous moveCoords
 * pause after comp moves piece
 *
 */

int main() {


    int testBoard[boardSize][boardSize] = {{0,0,0,0,0,0,0,-6},  //test chess board
                                       {0,0,0,0,0,0,0,-2},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,5,0,1,0,2,4},
                                       {6,0,0,0,0,0,0,0}
    };




    int fullBoard[boardSize][boardSize] = {{-2,-3,-4,-5,-6,-4,-3,-2}, //full chess board
                                       {-1,-1,-1,-1,-1,-1,-1,-1},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0},
                                       {1,1,1,1,1,1,1,1},
                                       {2,3,4,5,6,4,3,2}
    };





    runGame(fullBoard);



    return 0;
}