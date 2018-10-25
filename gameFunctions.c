//
// Created by shan on 3/14/18.
//

#include <stdio.h>
#include <memory.h>
#include "gameFunctions.h"
#include "pieces.h"
#include "comp.h"

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


void printBoard(int board[boardSize][boardSize]){
    printf("\n         A         B         C         D         E         F         G         H\n\n");

    for(int row = 0; row < boardSize; row++){

        printf("    ---------------------------------------------------------------------------------\n"); //each horizontal line except for last
        printf("    |         |         |         |         |         |         |         |         |\n"); //
        printf("%d   |", row+1); // prints grid number

        for(int col = 0; col < boardSize; col++){

            switch(board[row][col]){

                case wPawn:             //white pieces
                    printf("    p    ");
                    break;
                case wRook:
                    printf("    R    ");
                    break;
                case wKnight:
                    printf("    K    ");
                    break;
                case wBishop:
                    printf("    B    ");
                    break;
                case wQueen:
                    printf("    Q    ");
                    break;
                case wKing:
                    printf("    Kg   ");
                    break;

                case bPawn:             //black pieces
                    printf("   -p    ");
                    break;
                case bRook:
                    printf("   -R    ");
                    break;
                case bKnight:
                    printf("   -K    ");
                    break;
                case bBishop:
                    printf("   -B    ");
                    break;
                case bQueen:
                    printf("   -Q    ");
                    break;
                case bKing:
                    printf("   -Kg   ");
                    break;


                default:
                    printf("         ");
                    break;

            }
            printf("|"); // divides pieces next to each other
            if(col == boardSize-1)
                printf("   %d\n", row+1);

        }
        printf("    |         |         |         |         |         |         |         |         |\n");
    }
    printf("   ---------------------------------------------------------------------------------\n"); //last horizontal line
    printf("\n         A         B         C         D         E         F         G         H\n\n");

}

coords translate(char coordString[5]){  //Translates a string into coord struct
    coords temp;
    temp.xStart = coordString[0]-97; //subtractions convert ascii to int
    temp.yStart = coordString[1]-49;
    temp.xEnd = coordString[2]-97;
    temp.yEnd = coordString[3]-49;

    return temp;
}

void runGame(int board[boardSize][boardSize]){ //TODO: clean up whole function

    int quit = 0;
    int turns = 1;
    char currentMove[5];
    coords nextMove;

    //Prints ascii art of 'Dumb Chess'
    printf(" ____                             __                    ____       __                                 \n"
           "/\\  _`\\                          /\\ \\                  /\\  _`\\    /\\ \\                                \n"
           "\\ \\ \\/\\ \\   __  __    ___ ___    \\ \\ \\____             \\ \\ \\/\\_\\  \\ \\ \\___       __     ____    ____  \n"
           " \\ \\ \\ \\ \\ /\\ \\/\\ \\ /' __` __`\\   \\ \\ '__`\\             \\ \\ \\/_/_  \\ \\  _ `\\   /'__`\\  /',__\\  /',__\\ \n"
           "  \\ \\ \\_\\ \\\\ \\ \\_\\ \\/\\ \\/\\ \\/\\ \\   \\ \\ \\L\\ \\             \\ \\ \\L\\ \\  \\ \\ \\ \\ \\ /\\  __/ /\\__, `\\/\\__, `\\\n"
           "   \\ \\____/ \\ \\____/\\ \\_\\ \\_\\ \\_\\   \\ \\_,__/              \\ \\____/   \\ \\_\\ \\_\\\\ \\____\\\\/\\____/\\/\\____/\n"
           "    \\/___/   \\/___/  \\/_/\\/_/\\/_/    \\/___/                \\/___/     \\/_/\\/_/ \\/____/ \\/___/  \\/___/ \n"
           "                                                                                                      \n"
           "                                                                                                      ");
    printf("By Shan Kureshy\n\n welcome to My made-from-scratch Chess game! As the name implies, the computer you play against isn't the brightest, so go easy on him!\n\n"
           "To move, type the coordinates of the piece you want to move, then where you want to move it.\n"
           "E.G. To move the kings pawn to e7, type the command \"e5e7\"\n\n How many Players: \n\n\n");

    int numPlayers;
    scanf("%d", &numPlayers);
    if(numPlayers != 1 || numPlayers != 2)


    if(numPlayers ==1 ){
        printBoard(board);
        while(!quit){

            if(turns & 1) {  //if players turn
                printf("\n\n\nPlayer's move: ");

                scanf("%s", &currentMove); //TODO: replace with fgets()

                if (strcmp(currentMove, "quit") == 0) {
                    printf("Thank you for playing");
                    quit = 1;
                    continue;
                }
                printf("\n\n\n");

                nextMove = translate(currentMove);
            }
            else {
                nextMove = generateMove(board);
                printf("\n\nComputer's Move\n\n");
            }


            if(correctTurn(board, nextMove, turns)) //moveCoords if correct player is moving piece
                if(move(board, nextMove)) {
                    turns++; //Moves piece, and changes turn if moveCoords is valid
                }
                else
                    printf("\nInvalid Move!\n\n\n\n");

            else
                printf("\nInvalid Move!\n\n\n\n");

            printBoard(board);


        }



    }
    else if(numPlayers == 2){
        printBoard(board);
        while(!quit){

            if(turns & 1) {  //if players turn
                printf("\n\n\nPlayer 1's move: ");

                scanf("%s", &currentMove); //TODO: replace with fgets()

                if (strcmp(currentMove, "quit") == 0) {
                    printf("Thank you for playing");
                    quit = 1;
                    continue;
                }
                printf("\n\n\n");

                nextMove = translate(currentMove);
            }

            else if(!(turns & 1)) {  //if players turn
                printf("\n\n\nPlayer 2's move: ");

                scanf("%s", &currentMove); //TODO: replace with fgets()

                if (strcmp(currentMove, "quit") == 0) {
                    printf("Thank you for playing");
                    quit = 1;
                    continue;
                }
                printf("\n\n\n");

                nextMove = translate(currentMove);
            }

            if(correctTurn(board, nextMove, turns)) //moveCoords if correct player is moving piece
                if(move(board, nextMove)) {
                    turns++; //Moves piece, and changes turn if moveCoords is valid
                }
                else
                    printf("\nInvalid Move!\n\n\n\n");

            else
                printf("\nInvalid Move!\n\n\n\n");

            printBoard(board);

        }
    }

    else
        printf("\n\ncongrats, you already broke the game. Happy now?");
}
