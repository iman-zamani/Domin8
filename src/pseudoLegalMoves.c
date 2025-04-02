#include "define.h"
#include "board.h"
#include "move.h"
#include "moveList.h"

MoveList pseudoLegalWhitePawnMoves(Board *board){
    MoveList whitePawnMoves;
    initMoveList(&whitePawnMoves);
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_PAWN){
                int iIndex = i;
                int jIndex = j;
                // single pawn move that would not cause promotion 
                if (i >1 && board->squares[UP][j] == EMPTY){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    addMove(&whitePawnMoves,temp);
                }
                // single pawn move that would cause promotion 
                iIndex = i;
                jIndex = j;
                if (i == 1 && board->squares[UP][j] == EMPTY){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.promotionPieceType = WHITE_QUEEN;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_ROOK;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_KNIGHT;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_BISHOP;
                    addMove(&whitePawnMoves,temp);
                }
                // double pawn move
                iIndex = i;
                jIndex = j;
                if (i == 6 && board->squares[UP][j] == EMPTY && board->squares[UP][j] == EMPTY){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.pawnMovingTwoSquares = TRUE;
                    addMove(&whitePawnMoves,temp);
                }
                // right capture 
                iIndex = i;
                jIndex = j;
                if ((i > 1 && j < 7 && board->squares[UP][RIGHT] < EMPTY) || (i == 3 && (iIndex*8 + jIndex) == board->targetEnPassantSquare)){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                    addMove(&whitePawnMoves,temp);
                }
                // promotion with a right capture
                iIndex = i;
                jIndex = j;
                if (i == 1 && j < 7 && board->squares[UP][RIGHT] < EMPTY){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.promotionPieceType = WHITE_QUEEN;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_ROOK;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_KNIGHT;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_BISHOP;
                    addMove(&whitePawnMoves,temp);
                }
                // left capture 
                iIndex = i;
                jIndex = j;
                if ((i > 1 && j > 0 && board->squares[UP][LEFT] < EMPTY)  || (i == 3 && (iIndex*8 + jIndex) == board->targetEnPassantSquare)){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                    addMove(&whitePawnMoves,temp);
                }
                // promotion with a left capture
                iIndex = i;
                jIndex = j;
                if (i == 1 && j > 0 && board->squares[UP][LEFT] < EMPTY){
                    Move temp = createTempMove(WHITE_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.promotionPieceType = WHITE_QUEEN;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_ROOK;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_KNIGHT;
                    addMove(&whitePawnMoves,temp);
                    temp.promotionPieceType = WHITE_BISHOP;
                    addMove(&whitePawnMoves,temp);
                }
            }
        }
    }
    return whitePawnMoves;
}
MoveList pseudoLegalBlackPawnMoves(Board *board){
    MoveList blackPawnMoves;
    initMoveList(&blackPawnMoves);
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_PAWN){
                int iIndex = i;
                int jIndex = j;
                // single pawn move
                if (i < 6 && board->squares[DOWN][j] == EMPTY){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    addMove(&blackPawnMoves,temp);
                }
                // single pawn move that would cause promotion 
                iIndex = i;
                jIndex = j;
                if (i == 6 && board->squares[DOWN][j] == EMPTY){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.promotionPieceType = BLACK_QUEEN;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_ROOK;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_KNIGHT;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_BISHOP;
                    addMove(&blackPawnMoves,temp);
                }
                // double pawn move
                iIndex = i;
                jIndex = j;
                if (i == 1 && board->squares[DOWN][j] == EMPTY && board->squares[DOWN][j] == EMPTY){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.pawnMovingTwoSquares = TRUE;
                    addMove(&blackPawnMoves,temp);
                }
                // right capture 
                iIndex = i;
                jIndex = j;
                if ((i < 6 && j < 7 && board->squares[DOWN][RIGHT] < EMPTY)  || (i == 4 && (iIndex*8 + jIndex) == board->targetEnPassantSquare)){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                    addMove(&blackPawnMoves,temp);
                }
                // right capture  promotion 
                iIndex = i;
                jIndex = j;
                if (i == 6 && j < 7 && board->squares[DOWN][RIGHT] < EMPTY){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.promotionPieceType = BLACK_QUEEN;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_ROOK;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_KNIGHT;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_BISHOP;
                    addMove(&blackPawnMoves,temp);
                }
                // left capture
                iIndex = i;
                jIndex = j; 
                if ((i < 6 && j > 0 && board->squares[DOWN][LEFT] < EMPTY)  || (i == 4 && (iIndex*8 + jIndex) == board->targetEnPassantSquare)){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                    addMove(&blackPawnMoves,temp);
                }
                // left capture promotion 
                iIndex = i;
                jIndex = j;
                if (i == 6 && j > 0 && board->squares[DOWN][LEFT] < EMPTY){
                    Move temp = createTempMove(BLACK_PAWN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                    temp.promotionPieceType = BLACK_QUEEN;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_ROOK;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_KNIGHT;
                    addMove(&blackPawnMoves,temp);
                    temp.promotionPieceType = BLACK_BISHOP;
                    addMove(&blackPawnMoves,temp);
                }
            }
        }
    }
    return blackPawnMoves;
}


MoveList pseudoLegalWhiteRookMoves(Board *board){
    MoveList whiteRookMoves;
    initMoveList(&whiteRookMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_ROOK){
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                while(iIndex >0 && board->squares [UP][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] < EMPTY){
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteRookMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteRookMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteRookMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteRookMoves,temp);
                    }
                }
            }
        }
    }
    return whiteRookMoves;
}
MoveList pseudoLegalBlackRookMoves(Board *board){
    MoveList blackRookMoves;
    initMoveList(&blackRookMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_ROOK){
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                while(iIndex >0 && board->squares [UP][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] > EMPTY){
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackRookMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackRookMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackRookMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_ROOK,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackRookMoves,temp);
                    }
                }
            }
        }
    }
    return blackRookMoves;
}

MoveList pseudoLegalWhiteBishopMoves(Board *board){
    MoveList whiteBishopMoves;
    initMoveList(&whiteBishopMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_BISHOP){
                int iIndex = i;
                int jIndex = j;
                // how many we can go up right
                while(iIndex >0 && jIndex<7 && board->squares [UP][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteBishopMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex<7 && jIndex > 0 && board->squares [DOWN][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteBishopMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex<7 && jIndex < 7 && board->squares [DOWN][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteBishopMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteBishopMoves,temp);
                    }
                }
            }
        }
    }
    return whiteBishopMoves;
}
MoveList pseudoLegalBlackBishopMoves(Board *board){
    MoveList blackBishopMoves;
    initMoveList(&blackBishopMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_ROOK){
                int iIndex = i;
                int jIndex = j;
                // how many we can go up right 
                while(iIndex >0 && jIndex<7 && board->squares [UP][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackBishopMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex>0 && board->squares [DOWN][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackBishopMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex<7 && jIndex < 7 && board->squares [DOWN][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackBishopMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_BISHOP,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackBishopMoves,temp);
                    }
                }
            }
        }
    }
    return blackBishopMoves;
}

MoveList pseudoLegalWhiteQueenMoves(Board *board){
    MoveList whiteQueenMoves;
    initMoveList(&whiteQueenMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_QUEEN){
                // row and column moves -------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                while(iIndex >0 && board->squares [UP][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // moves that are like bishop------------------------------------------------------------
                iIndex = i;
                jIndex = j;
                // how many we can go up right
                while(iIndex >0 && jIndex<7 && board->squares[UP][RIGHT]<= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(WHITE_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteQueenMoves,temp);
                    }
                }
            }
        }
    }
    return whiteQueenMoves;
}
MoveList pseudoLegalBlackQueenMoves(Board *board){
    MoveList blackQueenMoves;
    initMoveList(&blackQueenMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_QUEEN){
                // row and column moves -------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                while(iIndex >0 && board->squares [UP][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // moves that are like bishop------------------------------------------------------------
                iIndex = i;
                jIndex = j;
                // how many we can go up right
                while(iIndex >0 && jIndex<7 && board->squares[UP][RIGHT]>= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp = createTempMove(BLACK_QUEEN,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackQueenMoves,temp);
                    }
                }
            }
        }
    }
    return blackQueenMoves;
}

MoveList pseudoLegalWhiteKingMoves(Board *board){
    MoveList whiteKingMoves;
    initMoveList(&whiteKingMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_KING){
                // row and column moves -------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                if(iIndex >0 && board->squares [UP][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && board->squares [DOWN][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                if(jIndex < 7 && board->squares [i][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                if(jIndex > 0 && board->squares [i][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // moves that are like bishop------------------------------------------------------------
                iIndex = i;
                jIndex = j;
                // how many we can go up right
                if(iIndex >0 && jIndex<7 && board->squares[UP][RIGHT]<= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // short castling 
                iIndex = i;
                jIndex = j;
                    if (board->whiteShortCastle == TRUE && i == 7 && j == 4 &&  board->squares [iIndex][RIGHT] == EMPTY &&  board->squares [iIndex][RIGHT] == EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        temp.shortCastle = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                // long castling 
                iIndex = i;
                jIndex = j;
                    if (board->whiteLongCastle == TRUE && i == 7 && j == 4 &&  board->squares [iIndex][LEFT] == EMPTY &&  board->squares [iIndex][LEFT] == EMPTY){
                        Move temp = createTempMove(WHITE_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        temp.longCastle = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                // there is only one white king 
                return whiteKingMoves;
            }
        }
    }
    return whiteKingMoves;
}
MoveList pseudoLegalBlackKingMoves(Board *board){
    MoveList blackKingMoves;
    initMoveList(&blackKingMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_KING){
                // row and column moves -------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                if(iIndex >0 && board->squares [UP][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && board->squares [DOWN][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                if(jIndex < 7 && board->squares [i][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                if(jIndex > 0 && board->squares [i][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // moves that are like bishop------------------------------------------------------------
                iIndex = i;
                jIndex = j;
                // how many we can go up right
                if(iIndex >0 && jIndex<7 && board->squares[UP][RIGHT]>= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] >= EMPTY){
                    
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKingMoves,temp);
                    }
                }
                 // short castling 
                 iIndex = i;
                 jIndex = j;
                if (board->blackShortCastle == TRUE && i == 0 && j == 4 &&  board->squares [iIndex][RIGHT] == EMPTY &&  board->squares [iIndex][RIGHT] == EMPTY){
                    Move temp = createTempMove(BLACK_KING,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                    temp.shortCastle = TRUE;
                    addMove(&blackKingMoves,temp);
                }
                 // long castling 
                 iIndex = i;
                 jIndex = j;
                if (board->blackLongCastle == TRUE && i == 0 && j == 4 && board->squares[iIndex][LEFT] == EMPTY && board->squares[iIndex][LEFT] == EMPTY){
                    Move temp = createTempMove(BLACK_KING, (i * 8 + j), (iIndex * 8 + jIndex), TRUE);
                    temp.longCastle = TRUE;
                    addMove(&blackKingMoves, temp);
                 }
                // there is only one black king 
                return blackKingMoves;
            }
        }
    }
    return blackKingMoves;
}

MoveList pseudoLegalWhiteKnightMoves(Board *board){
    MoveList whiteKnightMoves;
    initMoveList(&whiteKnightMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_KNIGHT){
                // a night has 8 possible moves at most 
                // if you imagine it like a circle the will line up to clock positions 
                // if we move clock wise it will be like this :
                // 1 2 4 5 7 8 10 11, I will define each so it will be easier to work with
                #define ONE [iIndex-=2][jIndex+=1]
                #define TWO [iIndex-=1][jIndex+=2]
                #define FOUR [iIndex+=1][jIndex+=2]
                #define FIVE [iIndex+=2][jIndex+=1]
                #define SEVEN [iIndex+=2][jIndex-=1]
                #define EIGHT [iIndex+=1][jIndex-=2]
                #define TEN [iIndex-=1][jIndex-=2]
                #define ELEVEN [iIndex-=2][jIndex-=1]
                int iIndex = i;
                int jIndex = j;
                
                // ------
                if(iIndex >1 && jIndex<7 && board->squares ONE <= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // -------
                iIndex = i;
                jIndex = j;
                if(iIndex >0 && jIndex <6 && board->squares TWO <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // -----
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 6 && board->squares FOUR <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // --------
                iIndex = i;
                jIndex = j;
                if( iIndex<6 &&jIndex < 7 && board->squares FIVE <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ---------------
                iIndex = i;
                jIndex = j;
                if(iIndex <6 && jIndex > 0 && board->squares SEVEN<= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ---------
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 1 && board->squares EIGHT <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ------------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 1 && board->squares TEN <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ----------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 1 && jIndex > 0 && board->squares ELEVEN <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(WHITE_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&whiteKnightMoves,temp);
                    }
                }
            }
        }
    }
    return whiteKnightMoves;
}
MoveList pseudoLegalBlackKnightMoves(Board *board){
    MoveList blackKnightMoves;
    initMoveList(&blackKnightMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_KNIGHT){
                // a night has 8 possible moves at most 
                // if you imagine it like a circle the will line up to clock positions 
                // if we move clock wise it will be like this :
                // 1 2 4 5 7 8 10 11, I will define each so it will be easier to work with
                #define ONE [iIndex-=2][jIndex+=1]
                #define TWO [iIndex-=1][jIndex+=2]
                #define FOUR [iIndex+=1][jIndex+=2]
                #define FIVE [iIndex+=2][jIndex+=1]
                #define SEVEN [iIndex+=2][jIndex-=1]
                #define EIGHT [iIndex+=1][jIndex-=2]
                #define TEN [iIndex-=1][jIndex-=2]
                #define ELEVEN [iIndex-=2][jIndex-=1]
                int iIndex = i;
                int jIndex = j;
                // ------
                if(iIndex >1 && jIndex<7 && board->squares ONE >= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // -------
                iIndex = i;
                jIndex = j;
                if(iIndex >0 && jIndex <6 && board->squares TWO >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // -----
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 6 && board->squares FOUR >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // --------
                iIndex = i;
                jIndex = j;
                if( iIndex<6 &&jIndex < 7 && board->squares FIVE >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ---------------
                iIndex = i;
                jIndex = j;
                if(iIndex <6 && jIndex > 0 && board->squares SEVEN >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ---------
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 1 && board->squares EIGHT >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ------------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 1 && board->squares TEN >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ----------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 1 && jIndex > 0 && board->squares ELEVEN >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),TRUE);
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp = createTempMove(BLACK_KNIGHT,(i*8 + j),(iIndex*8 + jIndex),FALSE);
                        addMove(&blackKnightMoves,temp);
                    }
                }
            }
        }
    }
    return blackKnightMoves;
}
