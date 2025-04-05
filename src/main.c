#include "define.h"
#include "board.h"
#include "move.h"
#include "moveList.h"
#include "pseudoLegalMoves.h"

int main(void){
    Board board;
    printf("Enter a FEN string: ");
    char string[100];
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = 0;
    readFenIntoBoard(&board,string);
    printBoard(&board);
    printf("legal moves :\n");
    int num = 0;
    MoveList temp = pseudoLegalWhitePawnMoves(&board);
    for (int k = 0;k<temp.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",temp.moves[k].startSquare, temp.moves[k].targetSquare);
    }
    num += temp.count;
    free(temp.moves);
    ///-------------------------
    temp = pseudoLegalWhiteRookMoves(&board);
    for (int k = 0;k<temp.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",temp.moves[k].startSquare, temp.moves[k].targetSquare);
    }
    num += temp.count;
    free(temp.moves);
    ///-------------------------
    temp = pseudoLegalWhiteKnightMoves(&board);
    for (int k = 0;k<temp.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",temp.moves[k].startSquare, temp.moves[k].targetSquare);
    }
    num += temp.count;
    free(temp.moves);
    ///-------------------------
    temp = pseudoLegalWhiteBishopMoves(&board);
    for (int k = 0;k<temp.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",temp.moves[k].startSquare, temp.moves[k].targetSquare);
    }
    num += temp.count;
    free(temp.moves);
    ///-------------------------
    temp = pseudoLegalWhiteQueenMoves(&board);
    for (int k = 0;k<temp.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",temp.moves[k].startSquare, temp.moves[k].targetSquare);
    }
    num += temp.count;
    free(temp.moves);
    ///-------------------------
    temp = pseudoLegalWhiteKingMoves(&board);
    for (int k = 0;k<temp.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",temp.moves[k].startSquare, temp.moves[k].targetSquare);
    }
    num += temp.count;
    free(temp.moves);
    printf("number of pseudoLegal moves for white: %d\n",num);
    printf("------------------------------------------\n");
    if (boardIsCheck(&board)){
        printf("board is in check\n");
    }
    else {
        printf("board is not in check\n");
    }
    
    return 0;
}

// for converting pseudo legal moves to legal move :
// concept of a pined pice or better say pice movement should not cuse reviling any attacks to the king 

// if the rook moves we should not be able to castle on that side (it should be added in apply move function)
// if the king moves we should be able to castle at all (it should be added in apply move function)
// if the rook gets captured , we should not be able to castle on that side 
// concept of check 
// concept of mate 
// if a pawn moves or a capture happens with should set the counter to zero (it should be added in apply move function)
