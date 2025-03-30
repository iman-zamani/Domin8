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
#define UP --iIndex
#define DOWN ++iIndex
#define RIGHT ++jIndex
#define LEFT --jIndex


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
struct MoveList{
    size_t count;     // how many moves are stored
    size_t capacity;  // total allocated number of moves we can have 
    Move* moves;
}typedef MoveList;
void initMoveList(MoveList * list){
    list->count = 0;
    list->capacity = 32;
    list->moves = NULL;
    list->moves = (Move*)malloc(list->capacity * sizeof(Move));  
    if (!list->moves) {
        perror("Memory allocation failed list moves");
        exit(EXIT_FAILURE);
    }
    // clearing the move buffer 
    for (int k = 0;k<list->capacity ;k++){
        list->moves[k].startSquare = -1;
        list->moves[k].targetSquare = -1;
        list->moves[k].enPassant = FALSE;
        list->moves[k].pawnMovingTwoSquares = FALSE;
        list->moves[k].castle = FALSE;
        list->moves[k].promotionToQueen = FALSE;
        list->moves[k].promotionToKnight = FALSE;
        list->moves[k].promotionToRook = FALSE;
        list->moves[k].promotionToBishop = FALSE;
        list->moves[k].capture = FALSE;

    }
}
void ensureMoveCapacity(MoveList* list) {
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        if (new_capacity == 0) new_capacity = 32;  
        Move* temp = realloc(list->moves, new_capacity * sizeof(Move));
        if (temp != NULL) {
            list->moves = temp;
            
            for (int k = list->capacity ;k<new_capacity ;k++){
                list->moves[k].startSquare = -1;
                list->moves[k].targetSquare = -1;
                list->moves[k].enPassant = FALSE;
                list->moves[k].pawnMovingTwoSquares = FALSE;
                list->moves[k].castle = FALSE;
                list->moves[k].promotionToQueen = FALSE;
                list->moves[k].promotionToKnight = FALSE;
                list->moves[k].promotionToRook = FALSE;
                list->moves[k].promotionToBishop = FALSE;
                list->moves[k].capture = FALSE;
        
            }
            list->capacity = new_capacity;
        } 
        else {
            perror("Failed to realloc memory in ensureMoveCapacity function");
            exit(EXIT_FAILURE);
        }
    }
}
void addMove(MoveList* list, Move move) {
    ensureMoveCapacity(list);
    list->moves[list->count++] = move;
}


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
MoveList legalWhiteRookMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteRookMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteRookMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteRookMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteRookMoves,temp);
                    }
                }
            }
        }
    }
    return whiteRookMoves;
}
MoveList legalBlackRookMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackRookMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackRookMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackRookMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackRookMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackRookMoves,temp);
                    }
                }
            }
        }
    }
    return blackRookMoves;
}

MoveList legalWhiteBishopMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteBishopMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex<7 && jIndex > 0 && board->squares [DOWN][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteBishopMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex<7 && jIndex < 7 && board->squares [DOWN][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteBishopMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteBishopMoves,temp);
                    }
                }
            }
        }
    }
    return whiteBishopMoves;
}
MoveList legalBlackBishopMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackBishopMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex>0 && board->squares [DOWN][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackBishopMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex<7 && jIndex < 7 && board->squares [DOWN][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackBishopMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackBishopMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackBishopMoves,temp);
                    }
                }
            }
        }
    }
    return blackBishopMoves;
}

MoveList legalWhiteQueenMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteQueenMoves,temp);
                    }
                }
            }
        }
    }
    return whiteQueenMoves;
}

MoveList legalBlackQueenMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackQueenMoves,temp);
                        break;
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackQueenMoves,temp);
                    }
                }
            }
        }
    }
    return blackQueenMoves;
}

int main(){
    Board board;
    printf("Enter a FEN string: ");
    char string[100];
    scanf("%s",string);
    readFenIntoBoard(&board,string);
    printBoard(&board);
    printf("legal moves :\n");
    MoveList whiteRookMoves = legalWhiteQueenMoves(&board);
    for (int k = 0;k<whiteRookMoves.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",whiteRookMoves.moves[k].startSquare, whiteRookMoves.moves[k].targetSquare);
    }
    return 0;
}