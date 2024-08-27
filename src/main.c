#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
struct Board{
    bool isWhiteTurn;

    // 
    uint64_t whitePieces;
    uint64_t blackPieces;

    uint64_t allPieces;
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

/**
 * it will set the nth bit of the 64 bit number.
 * 
 * @param number the 64-bit unsigned integer.
 * @param n the bit position to set to one (0-based, where 0 is the least significant bit).
 */
void setNthBit(uint64_t* number, int n) {
    *number |= ((uint64_t)1 << n);
}

/**
 * it will initialize the board to starting position 
 * with this FEN:
 * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1.
 * @param board the entire board object that you want to modify.
 */
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
    //
    board->allPieces = board->whitePieces | board->blackPieces;
    // it is what turn 
    board->isWhiteTurn = true;
    // castle rights default to true at game start.
    board->whiteKingCastle = true;
    board->whiteQueenCastle = true;
    board->blackKingCastle = true;
    board->blackQueenCastle = true;

    // en passant target defaults (no en passant possible initially)
    board->targetEnPassantX = -1; 
    board->targetEnPassantY = -1;
}
void printUint64(uint64_t status){
    printf("----------------\n");
    for (int i=63;i>=0;i--){
        if (isNthBitSet(status,i)){
            printf("1 ");
        }
        else {
            printf("0 ");
        }
        if (i % 8 == 0){
                printf("\n");
            }
    }
    printf("----------------\n");
}
void printBoard(Board* board){
    for (int i=63;i>=0;i--){
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
            printf(". ");
        }
        if (i % 8 == 0){
                printf("\n");
            }
    }
}



/**
 * it will return the legal moves that this pawn can do (pseudo legal move).
 * 
 * @param board the entire board object.
 * @param x the column that the piece is in (0,0) is top left.
 * @param y the row that the piece is in (0,0) is top left.
 * @return a 64 bit number for each square . each square (bit) that is set to one 
 * @return it means that piece can go to that square 
 * 
 */
uint64_t whitePawnLegalMoves(Board* board,int x ,int y){
    uint64_t legalSquares = 0x0000000000000000ULL;
    // if the square in front the pawn is free
    if (isNthBitSet(board->allPieces,(y-1)*8+x)){
        setNthBit(&legalSquares,(y-1)*8+x);
        // if the pawn is at start and two squares in front it is free
        if (y == 6 &&  isNthBitSet(board->allPieces,4*8+x)){
            setNthBit(&legalSquares,4*8+x);
        }
    }
    // left capture 
    if (x%8 != 0 && isNthBitSet(board->blackPieces,(y-1)*8+(x-1))){
        setNthBit(&legalSquares,(y-1)*8+(x-1));
    }
    // right capture 
    if (x%8 != 7 && isNthBitSet(board->blackPieces,(y-1)*8+(x+1))){
        setNthBit(&legalSquares,(y-1)*8+(x+1));
    }
    return legalSquares;
    
}
/**
 * it will return the legal moves that this pawn can do (pseudo legal move).
 * 
 * @param board the entire board object.
 * @param x the column that the piece is in (0,0) is top left.
 * @param y the row that the piece is in (0,0) is top left.
 * @return a 64 bit number for each square . each square (bit) that is set to one 
 * @return it means that piece can go to that square 
 * 
 */
uint64_t blackPawnLegalMoves(Board* board,int x ,int y){
    uint64_t legalSquares = 0x0000000000000000ULL;
    // if the square in front the pawn is free
    if (isNthBitSet(board->allPieces,(y+1)*8+x)){
        setNthBit(&legalSquares,(y+1)*8+x);
        // if the pawn is at start and two squares in front it is free
        if (y == 6 &&  isNthBitSet(board->allPieces,3*8+x)){
            setNthBit(&legalSquares,3*8+x);
        }
    }
    // left capture 
    if (x%8 != 0 && isNthBitSet(board->blackPieces,(y+1)*8+(x-1))){
        setNthBit(&legalSquares,(y+1)*8+(x-1));
    }
    // right capture 
    if (x%8 != 7 && isNthBitSet(board->blackPieces,(y+1)*8+(x+1))){
        setNthBit(&legalSquares,(y+1)*8+(x+1));
    }
    return legalSquares;
    
}

uint64_t whiteRookLegalMoves(Board* board, int x, int y) {
    uint64_t legalSquares = 0x0000000000000000ULL;

    // how many squares it can go up
    for (int up = 1; y - up >= 0; up++) {
        if (isNthBitSet(board->whitePieces, (y - up) * 8 + x))
            break;
        setNthBit(&legalSquares, (y - up) * 8 + x);
        if (isNthBitSet(board->blackPieces, (y - up) * 8 + x))
            break;
    }
    // how many squares it can go down
    for (int down = 1; y + down < 8; down++) {
        if (isNthBitSet(board->whitePieces, (y + down) * 8 + x))
            break;
        setNthBit(&legalSquares, (y + down) * 8 + x);
        if (isNthBitSet(board->blackPieces, (y + down) * 8 + x))
            break;
    }
    // how many squares it can go right
    for (int right = 1; x + right < 8; right++) {
        if (isNthBitSet(board->whitePieces, y * 8 + x + right))
            break;
        setNthBit(&legalSquares, y * 8 + x + right);
        if (isNthBitSet(board->blackPieces, y * 8 + x + right))
            break;
    }
    // how many squares it can go left
    for (int left = 1; x - left >= 0; left++) {
        if (isNthBitSet(board->whitePieces, y * 8 + x - left))
            break;
        setNthBit(&legalSquares, y * 8 + x - left);
        if (isNthBitSet(board->blackPieces, y * 8 + x - left))
            break;
    }
    return legalSquares;
}

uint64_t blackRookLegalMoves(Board* board, int x, int y) {
    uint64_t legalSquares = 0x0000000000000000ULL;

    // how many squares it can go up
    for (int up = 1; y - up >= 0; up++) {
        if (isNthBitSet(board->blackPieces, (y - up) * 8 + x))
            break;
        setNthBit(&legalSquares, (y - up) * 8 + x);
        if (isNthBitSet(board->whitePieces, (y - up) * 8 + x))
            break;
    }
    // how many squares it can go down
    for (int down = 1; y + down < 8; down++) {
        if (isNthBitSet(board->blackPieces, (y + down) * 8 + x))
            break;
        setNthBit(&legalSquares, (y + down) * 8 + x);
        if (isNthBitSet(board->whitePieces, (y + down) * 8 + x))
            break;
    }
    // how many squares it can go right
    for (int right = 1; x + right < 8; right++) {
        if (isNthBitSet(board->blackPieces, y * 8 + x + right))
            break;
        setNthBit(&legalSquares, y * 8 + x + right);
        if (isNthBitSet(board->whitePieces, y * 8 + x + right))
            break;
    }
    // how many squares it can go left
    for (int left = 1; x - left >= 0; left++) {
        if (isNthBitSet(board->blackPieces, y * 8 + x - left))
            break;
        setNthBit(&legalSquares, y * 8 + x - left);
        if (isNthBitSet(board->whitePieces, y * 8 + x - left))
            break;
    }
    return legalSquares;
}

void whiteBishopLegalMoves(Board* board, int x, int y) {
    uint64_t legalSquares = 0x0000000000000000ULL;
    //up right
    for (int right = 1,up = 1; x + right < 8 && y - up >= 0; right++,up++) {
        if (isNthBitSet(board->whitePieces,  (y - up) * 8 + x + right))
            break;
        setNthBit(&legalSquares,  (y - up) * 8 + x + right);
        if (isNthBitSet(board->blackPieces,  (y - up) * 8 + x + right))
            break;
    }
    //up left
    for (int left = 1,up = 1; x - left >= 0 && y - up >= 0; left++,up++) {
        if (isNthBitSet(board->whitePieces,  (y - up) * 8 + x - left))
            break;
        setNthBit(&legalSquares,  (y - up) * 8 + x - left);
        if (isNthBitSet(board->blackPieces,  (y - up) * 8 + x -left))
            break;
    }
    //down right 
    for (int right = 1,down = 1; x + right < 8 && y + down < 8; right++,down++) {
        if (isNthBitSet(board->whitePieces,  (y + down) * 8 + x + right))
            break;
        setNthBit(&legalSquares,  (y + down) * 8 + x + right);
        if (isNthBitSet(board->blackPieces,  (y + down) * 8 + x + right))
            break;
    }
    //down left 
    for (int left = 1,down = 1; x - left >= 0 && y + down < 8; left++,down++) {
        if (isNthBitSet(board->whitePieces,  (y + down) * 8 + x - left))
            break;
        setNthBit(&legalSquares,  (y + down) * 8 + x - left);
        if (isNthBitSet(board->blackPieces,  (y + down) * 8 + x - left))
            break;
    }

    return legalSquares;
}
void blackBishopLegalMoves(Board* board, int x, int y) {
    uint64_t legalSquares = 0x0000000000000000ULL;
    //up right
    for (int right = 1,up = 1; x + right < 8 && y - up >= 0; right++,up++) {
        if (isNthBitSet(board->blackPieces,  (y - up) * 8 + x + right))
            break;
        setNthBit(&legalSquares,  (y - up) * 8 + x + right);
        if (isNthBitSet(board->whitePieces,  (y - up) * 8 + x + right))
            break;
    }
    //up left
    for (int left = 1,up = 1; x - left >= 0 && y - up >= 0; left++,up++) {
        if (isNthBitSet(board->blackPieces,  (y - up) * 8 + x - left))
            break;
        setNthBit(&legalSquares,  (y - up) * 8 + x - left);
        if (isNthBitSet(board->whitePieces,  (y - up) * 8 + x -left))
            break;
    }
    //down right 
    for (int right = 1,down = 1; x + right < 8 && y + down < 8; right++,down++) {
        if (isNthBitSet(board->blackPieces,  (y + down) * 8 + x + right))
            break;
        setNthBit(&legalSquares,  (y + down) * 8 + x + right);
        if (isNthBitSet(board->whitePieces,  (y + down) * 8 + x + right))
            break;
    }
    //down left 
    for (int left = 1,down = 1; x - left >= 0 && y + down < 8; left++,down++) {
        if (isNthBitSet(board->blackPieces,  (y + down) * 8 + x - left))
            break;
        setNthBit(&legalSquares,  (y + down) * 8 + x - left);
        if (isNthBitSet(board->whitePieces,  (y + down) * 8 + x - left))
            break;
    }

    return legalSquares;
}


int main(){
    Board chessBoard;
    initBoard(&chessBoard);
    printBoard(&chessBoard);
    return 0;
}

