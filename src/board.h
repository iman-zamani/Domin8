#pragma once 
typedef struct Board{
    //         [row][column]
    int squares[8][8] ;
    bool whiteShortCastle;
    bool whiteLongCastle;
    bool blackShortCastle;
    bool blackLongCastle;
    bool isWhiteTurn;
    int targetEnPassantSquare;
    int halfMovesFromLastCaptureOrPawnMove;
    int numFullMoves;
}Board;

void readFenIntoBoard(Board * board ,char * FEN);
void printBoard(Board *board);
bool boardIsCheck(Board *board);
