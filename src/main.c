#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
// values for filling squares 
#define WHITE_ROOK 5
#define WHITE_KNIGHT 3 
#define WHITE_BISHOP 4
#define WHITE_PAWN  1
#define WHITE_QUEEN  9
#define WHITE_KING 10

#define BLACK_ROOK  -5
#define BLACK_KNIGHT -3
#define BLACK_BISHOP -4
#define BLACK_PAWN  -1
#define BLACK_QUEEN  -9
#define BLACK_KING  -10

#define EMPTY 0


// directions and boundaries


struct Board{
    //         [row][column]
    int squares[8][8] ;
}typedef Board;
void readFenIntoBoard(Board * board ,char * FEN){
    int fenIndex = 0;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            char c = FEN[fenIndex];
            if (c > '0' && c < '9'){
                for (int k=0;k<(c-'0');k++){
                    board->squares[i][j+k] = EMPTY;
                }
                j = j + (c - '1');
                fenIndex++;
                continue;
            }
            switch (c){
                case 'r':
                    board->squares[i][j] = BLACK_ROOK;
                    break;
                case 'q':
                    board->squares[i][j] = BLACK_QUEEN;
                    break;
                case 'b':
                    board->squares[i][j] = BLACK_BISHOP;
                    break;
                case 'n':
                    board->squares[i][j] = BLACK_KNIGHT;
                    break;
                case 'k':
                    board->squares[i][j] = BLACK_KING;
                    break;
                case 'p':
                    board->squares[i][j] = BLACK_PAWN;
                    break;
                case 'R':
                    board->squares[i][j] = WHITE_ROOK;
                    break;
                case 'Q':
                    board->squares[i][j] = WHITE_QUEEN;
                    break;
                case 'B':
                    board->squares[i][j] = WHITE_BISHOP;
                    break;
                case 'N':
                    board->squares[i][j] = WHITE_KNIGHT;
                    break;
                case 'K':
                    board->squares[i][j] = WHITE_KING;
                    break;
                case 'P':
                    board->squares[i][j] = WHITE_PAWN;
                    break;
            }
            fenIndex++;
        }
        fenIndex++;
    }
}
void printBoard(Board *board){
    //board->squares[2][2] = BLACK_BISHOP;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            switch (board->squares[i][j]){
                case WHITE_ROOK: 
                    printf(" R");
                    break;
                case WHITE_KNIGHT: 
                    printf(" N");
                    break;
                case WHITE_BISHOP: 
                    printf(" B");  
                    break;
                case WHITE_PAWN: 
                    printf(" P");
                    break;
                case WHITE_QUEEN: 
                    printf(" Q");
                    break;
                case WHITE_KING: 
                    printf(" K"); 
                    break; 
                case BLACK_ROOK: 
                    printf(" r");
                    break;
                case BLACK_KNIGHT: 
                    printf(" n");
                    break;
                case BLACK_BISHOP: 
                    printf(" b"); 
                    break; 
                case BLACK_PAWN: 
                    printf(" p");
                    break;
                case BLACK_QUEEN: 
                    printf(" q");
                    break;
                case BLACK_KING: 
                    printf(" k"); 
                    break;     
                case EMPTY:
                    printf(" .");  
                    break;
                default:
                    perror("\nERROR, invalid FEN string\n");
                    exit(EXIT_FAILURE);
                    break;       
            }
        }
        printf("\n");
    }
    return ;
}
struct Move{
    int startSquare;
    int targetSquare;
    bool capture;
    bool enPassant;
    bool pawnMovingTwoSquares;
    bool castle;
    bool promotionToQueen;
    bool promotionToKnight;
    bool promotionToRook;
    bool promotionToBishop;
}typedef Move;


Move *legalWhitePawnMoves(Board *board){
    Move* whitePawnMoves = NULL;
    whitePawnMoves = (Move*)malloc(32 * sizeof(Move));  
    if (!whitePawnMoves) {
        perror("Memory allocation failed for white pawn legal moves");
        exit(EXIT_FAILURE);
    }
    // clearing the move buffer 
    for (int k = 0;k<32 && whitePawnMoves[k].startSquare != -1;k++){
        whitePawnMoves[k].startSquare = -1;
        whitePawnMoves[k].targetSquare = -1;
        whitePawnMoves[k].enPassant = FALSE;
        whitePawnMoves[k].pawnMovingTwoSquares = FALSE;
        whitePawnMoves[k].castle = FALSE;
        whitePawnMoves[k].promotionToQueen = FALSE;
        whitePawnMoves[k].promotionToKnight = FALSE;
        whitePawnMoves[k].promotionToRook = FALSE;
        whitePawnMoves[k].promotionToBishop = FALSE;
        whitePawnMoves[k].capture = FALSE;

    }
    int index = 0;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_PAWN){
                // single pawn move
                if (i > 0 && board->squares[i-1][j] == EMPTY){
                    whitePawnMoves[index].startSquare = i*8 + j;
                    whitePawnMoves[index].targetSquare = (i-1)*8 + j;
                    index++;
                }
                // double pawn move
                if (i == 6 && board->squares[i-2][j] == EMPTY && board->squares[i-1][j] == EMPTY){
                    whitePawnMoves[index].pawnMovingTwoSquares = TRUE;
                    whitePawnMoves[index].startSquare = i*8 + j;
                    whitePawnMoves[index].targetSquare = (i-2)*8 + j;
                    index++;
                }
                // right capture 
                if (i > 0 && j < 7 && board->squares[i-1][j+1] < EMPTY){
                    whitePawnMoves[index].capture = TRUE;
                    whitePawnMoves[index].startSquare = i*8 + j;
                    whitePawnMoves[index].targetSquare = (i-1)*8 + j + 1;
                    index++;
                }
                // left capture 
                if (i > 0 && j > 0 && board->squares[i-1][j-1] < EMPTY){
                    whitePawnMoves[index].capture = TRUE;
                    whitePawnMoves[index].startSquare = i*8 + j;
                    whitePawnMoves[index].targetSquare = (i-1)*8 + j - 1;
                    index++;
                }
            }
        }
    }
    return whitePawnMoves;
}
Move *legalBlackPawnMoves(Board *board){
    Move* blackPawnMoves = NULL;
    blackPawnMoves = (Move*)malloc(32 * sizeof(Move));  
    if (!blackPawnMoves) {
        perror("Memory allocation failed for black pawn legal moves");
        exit(EXIT_FAILURE);
    }
    // clearing the move buffer 
    for (int k = 0;k<32 && blackPawnMoves[k].startSquare != -1;k++){
        blackPawnMoves[k].startSquare = -1;
        blackPawnMoves[k].targetSquare = -1;
        blackPawnMoves[k].enPassant = FALSE;
        blackPawnMoves[k].pawnMovingTwoSquares = FALSE;
        blackPawnMoves[k].castle = FALSE;
        blackPawnMoves[k].promotionToQueen = FALSE;
        blackPawnMoves[k].promotionToKnight = FALSE;
        blackPawnMoves[k].promotionToRook = FALSE;
        blackPawnMoves[k].promotionToBishop = FALSE;
        blackPawnMoves[k].capture = FALSE;

    }
    int index = 0;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_PAWN){
                // single pawn move
                if (i < 7 && board->squares[i+1][j] == EMPTY){
                    blackPawnMoves[index].startSquare = i*8 + j;
                    blackPawnMoves[index].targetSquare = (i+1)*8 + j;
                    index++;
                }
                // double pawn move
                if (i == 1 && board->squares[i+2][j] == EMPTY && board->squares[i+1][j] == EMPTY){
                    blackPawnMoves[index].pawnMovingTwoSquares = TRUE;
                    blackPawnMoves[index].startSquare = i*8 + j;
                    blackPawnMoves[index].targetSquare = (i+2)*8 + j;
                    index++;
                }
                // right capture 
                if (i < 7 && j < 7 && board->squares[i+1][j+1] < EMPTY){
                    blackPawnMoves[index].capture = TRUE;
                    blackPawnMoves[index].startSquare = i*8 + j;
                    blackPawnMoves[index].targetSquare = (i+1)*8 + j + 1;
                    index++;
                }
                // left capture 
                if (i < 7 && j > 0 && board->squares[i+1][j-1] < EMPTY){
                    blackPawnMoves[index].capture = TRUE;
                    blackPawnMoves[index].startSquare = i*8 + j;
                    blackPawnMoves[index].targetSquare = (i+1)*8 + j - 1;
                    index++;
                }
            }
        }
    }
    return blackPawnMoves;
}
int main(){
    Board board;
    printf("Enter a FEN string: ");
    char string[100];
    scanf("%s",string);
    readFenIntoBoard(&board,string);
    printBoard(&board);
    printf("legal moves :\n");
    Move * whitePawnMoves = legalWhitePawnMoves(&board);
    for (int k = 0;k<32 && whitePawnMoves[k].startSquare != -1;k++){
        printf("start square: %d\ttargetSquare: %d\n",whitePawnMoves[k].startSquare, whitePawnMoves[k].targetSquare);
    }
    return 0;
}