#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
struct Board{
    uint64_t whitePieces;
    uint64_t blackPieces;
    // bit board representation of each piece 
    uint64_t whiteRook;
    uint64_t whiteKnight;
    uint64_t whiteBishop;
    uint64_t whitePawn;
    uint64_t whiteQueen;
    uint64_t whiteKing;

    uint64_t blackRook;
    uint64_t blackKnight;
    uint64_t blackBishop;
    uint64_t blackPawn;
    uint64_t blackQueen;
    uint64_t blackKing;

    // right of castling for each color and each side 
    bool whiteKingCastle;
    bool whiteQueenCastle;

    bool blackKingCastle;
    bool blackQueenCastle;

    // Use -1 to denote invalid/no target.
    int targetEnPassantX, targetEnPassantY;


}typedef Board;

/**
 * checks if the nth bit of a 64-bit unsigned integer is set.
 * 
 * @param number the 64-bit unsigned integer.
 * @param n the bit position to check (0-based, where 0 is the least significant bit).
 * @return true if the nth bit is set to 1, otherwise false.
 */
bool isNthBitSet(uint64_t number, int n) {
    if (n < 0 || n >= 64) {
        // out of range, return false.
        return false;
    }

    // Create a mask with only the nth bit set.
    uint64_t mask = 1ULL << n;

    // Use bitwise AND to determine if the nth bit is set.
    return (number & mask) != 0;
}
void initBoard(Board* board) {
    // initialize bitBoards for a standard chess game.
    board->whiteRook   = 0x0000000000000081ULL;
    board->whiteKnight = 0x0000000000000042ULL;
    board->whiteBishop = 0x0000000000000024ULL;
    board->whiteQueen  = 0x0000000000000010ULL;
    board->whiteKing   = 0x0000000000000008ULL;
    board->whitePawn   = 0x000000000000FF00ULL;
    board->whitePieces = board->whiteRook | board->whiteKnight | board->whiteBishop | board->whitePawn | board->whiteQueen | board->whiteKing;

    board->blackRook   = 0x8100000000000000ULL;
    board->blackKnight = 0x4200000000000000ULL;
    board->blackBishop = 0x2400000000000000ULL;
    board->blackQueen  = 0x1000000000000000ULL;
    board->blackKing   = 0x0800000000000000ULL;
    board->blackPawn   = 0x00FF000000000000ULL;
    board->blackPieces = board->blackRook | board->blackKnight | board->blackBishop | board->blackPawn | board->blackQueen | board->blackKing;

    // castle rights default to true at game start.
    board->whiteKingCastle = true;
    board->whiteQueenCastle = true;
    board->blackKingCastle = true;
    board->blackQueenCastle = true;

    // en passant target defaults (no en passant possible initially)
    board->targetEnPassantX = -1; 
    board->targetEnPassantY = -1;
}

void printBoard(Board* board){
    for (int i=0;i<64;i++){
        if(isNthBitSet(board->whitePieces,i)){
            if(isNthBitSet(board->whitePawn,i)){
                printf("P ");
            }
            else if(isNthBitSet(board->whiteQueen,i)){
                printf("Q ");
            }
            else if(isNthBitSet(board->whiteRook,i)){
                printf("R ");
            }
            else if(isNthBitSet(board->whiteKnight,i)){
                printf("N ");
            }
            else if(isNthBitSet(board->whiteBishop,i)){
                printf("B ");
            }
            else if(isNthBitSet(board->whiteKing,i)){
                printf("K ");
            }
        }



        else if(isNthBitSet(board->blackPieces,i)){
            if(isNthBitSet(board->blackPawn,i)){
                printf("p ");
            }
            else if(isNthBitSet(board->blackQueen,i)){
                printf("q ");
            }
            else if(isNthBitSet(board->blackRook,i)){
                printf("r ");
            }
            else if(isNthBitSet(board->blackKnight,i)){
                printf("n ");
            }
            else if(isNthBitSet(board->blackBishop,i)){
                printf("b ");
            }
            else if(isNthBitSet(board->blackKing,i)){
                printf("k ");
            }
        }



        else {
            printf("  ");
        }
        if (i % 8 == 7){
                printf("\n");
            }
    }
}
void printBoard2(Board* board) {
    for (int rank = 7; rank >= 0; rank--) {  // Loop from rank 8 to rank 1
        for (int file = 0; file < 8; file++) {  // Loop from file a to file h
            int i = rank * 8 + file;  // Calculate the bit index
            if (isNthBitSet(board->whitePieces, i)) {
                if (isNthBitSet(board->whitePawn, i)) {
                    printf("P ");
                } else if (isNthBitSet(board->whiteQueen, i)) {
                    printf("Q ");
                } else if (isNthBitSet(board->whiteRook, i)) {
                    printf("R ");
                } else if (isNthBitSet(board->whiteKnight, i)) {
                    printf("N ");
                } else if (isNthBitSet(board->whiteBishop, i)) {
                    printf("B ");
                } else if (isNthBitSet(board->whiteKing, i)) {
                    printf("K ");
                }
            } else if (isNthBitSet(board->blackPieces, i)) {
                if (isNthBitSet(board->blackPawn, i)) {
                    printf("p ");
                } else if (isNthBitSet(board->blackQueen, i)) {
                    printf("q ");
                } else if (isNthBitSet(board->blackRook, i)) {
                    printf("r ");
                } else if (isNthBitSet(board->blackKnight, i)) {
                    printf("n ");
                } else if (isNthBitSet(board->blackBishop, i)) {
                    printf("b ");
                } else if (isNthBitSet(board->blackKing, i)) {
                    printf("k ");
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main(){
    Board chessBoard;
    initBoard(&chessBoard);
    printBoard2(&chessBoard);
    return 0;
}