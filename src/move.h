#pragma once 
#include "define.h"
typedef struct Move{
    int pieceType;
    int startSquare;
    int targetSquare;
    bool isCapture;
    bool enPassant; // yet to be added 
    bool pawnMovingTwoSquares;
    bool shortCastle;
    bool longCastle;
    int promotionPieceType;
}Move;


Move createTempMove(int tPieceType, int tStartSquare, int tTargetSquare, bool tIsCapture);
