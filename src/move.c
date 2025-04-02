#include "move.h"

Move createTempMove(int tPieceType, int tStartSquare, int tTargetSquare, bool tIsCapture){
    Move temp;
   temp.startSquare = tStartSquare;
   temp.targetSquare = tTargetSquare;
   temp.pieceType = tPieceType;
   temp.isCapture = tIsCapture;
   // castle checking 
   if (tPieceType == WHITE_KING && tStartSquare == 60 && tTargetSquare == 62){
    temp.shortCastle = TRUE;
   }
   else if (tPieceType == WHITE_KING && tStartSquare == 60 && tTargetSquare == 58){
    temp.longCastle = TRUE;
   }
   else if (tPieceType == BLACK_KING && tStartSquare == 4 && tTargetSquare == 6){
    temp.shortCastle = TRUE;
   }
   else if (tPieceType == BLACK_KING && tStartSquare == 4 && tTargetSquare == 2){
    temp.longCastle = TRUE;
   }
   else {
    temp.shortCastle = FALSE;
    temp.longCastle = FALSE;
   }
   // if it needs modifications for the below atributes 
   // they should be handled by the legal moves finder function itself 
    temp.enPassant = FALSE;
    temp.pawnMovingTwoSquares = FALSE;
    temp.promotionPieceType = EMPTY;
    
   return temp;
}
