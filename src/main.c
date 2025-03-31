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


MoveList legalWhitePawnMoves(Board *board){
    MoveList whitePawnMoves;
    initMoveList(&whitePawnMoves);
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_PAWN){
                int iIndex = i;
                int jIndex = j;
                // single pawn move
                if (i > 0 && board->squares[UP][j] == EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&whitePawnMoves,temp);
                }
                // double pawn move
                iIndex = i;
                jIndex = j;
                if (i == 6 && board->squares[UP][j] == EMPTY && board->squares[UP][j] == EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&whitePawnMoves,temp);
                }
                // right capture 
                iIndex = i;
                jIndex = j;
                if (i > 0 && j < 7 && board->squares[UP][RIGHT] < EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&whitePawnMoves,temp);
                }
                // left capture 
                iIndex = i;
                jIndex = j;
                if (i > 0 && j > 0 && board->squares[UP][LEFT] < EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&whitePawnMoves,temp);
                }
            }
        }
    }
    return whitePawnMoves;
}
MoveList legalBlackPawnMoves(Board *board){
    MoveList blackPawnMoves;
    initMoveList(&blackPawnMoves);
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_PAWN){
                int iIndex = i;
                int jIndex = j;
                // single pawn move
                if (i < 7 && board->squares[UP][j] == EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&blackPawnMoves,temp);
                }
                // double pawn move
                iIndex = i;
                jIndex = j;
                if (i == 1 && board->squares[UP][j] == EMPTY && board->squares[UP][j] == EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&blackPawnMoves,temp);
                }
                // right capture 
                iIndex = i;
                jIndex = j;
                if (i < 7 && j < 7 && board->squares[UP][RIGHT] < EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&blackPawnMoves,temp);
                }
                // left capture
                iIndex = i;
                jIndex = j; 
                if (i < 7 && j > 0 && board->squares[UP][LEFT] < EMPTY){
                    Move temp;
                    temp.startSquare = i*8 + j;
                    temp.targetSquare = iIndex*8 + jIndex;
                    addMove(&blackPawnMoves,temp);
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

MoveList legalWhiteKingMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && board->squares [DOWN][j] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                if(jIndex < 7 && board->squares [i][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                if(jIndex > 0 && board->squares [i][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKingMoves,temp);
                    }
                }
                // there is only one white king 
                return whiteKingMoves;
            }
        }
    }
    return whiteKingMoves;
}

MoveList legalBlackKingMoves(Board *board){
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && board->squares [DOWN][j] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                if(jIndex < 7 && board->squares [i][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                if(jIndex > 0 && board->squares [i][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
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
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] >= EMPTY){
                    
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKingMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKingMoves,temp);
                    }
                }
                // there is only one black king 
                return blackKingMoves;
            }
        }
    }
    return blackKingMoves;
}

MoveList legalWhiteKnightMoves(Board *board){
    MoveList whiteKnightMoves;
    initMoveList(&whiteKnightMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == WHITE_KNIGHT){
                // row and column moves -------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
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
                // ------
                if(iIndex >1 && jIndex<7 && board->squares ONE <= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // -------
                iIndex = i;
                jIndex = j;
                if(iIndex >0 && jIndex <6 && board->squares TWO <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // -----
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 6 && board->squares FOUR <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // --------
                iIndex = i;
                jIndex = j;
                if( iIndex<6 &&jIndex < 7 && board->squares FIVE <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ---------------
                iIndex = i;
                jIndex = j;
                if(iIndex <6 && jIndex > 0 && board->squares SEVEN<= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ---------
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 1 && board->squares EIGHT <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ------------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 1 && board->squares TEN <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
                // ----------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 1 && jIndex > 0 && board->squares ELEVEN <= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] < EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&whiteKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&whiteKnightMoves,temp);
                    }
                }
            }
        }
    }
    return whiteKnightMoves;
}
MoveList legalBlackKnightMoves(Board *board){
    MoveList blackKnightMoves;
    initMoveList(&blackKnightMoves);
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == BLACK_KNIGHT){
                // row and column moves -------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
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
                // ------
                if(iIndex >1 && jIndex<7 && board->squares ONE >= EMPTY){
                    // capture
                    if (board->squares [iIndex][j] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // -------
                iIndex = i;
                jIndex = j;
                if(iIndex >0 && jIndex <6 && board->squares TWO >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // -----
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 6 && board->squares FOUR >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // --------
                iIndex = i;
                jIndex = j;
                if( iIndex<6 &&jIndex < 7 && board->squares FIVE >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ---------------
                iIndex = i;
                jIndex = j;
                if(iIndex <6 && jIndex > 0 && board->squares SEVEN >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ---------
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 1 && board->squares EIGHT >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ------------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 1 && board->squares TEN >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
                // ----------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 1 && jIndex > 0 && board->squares ELEVEN >= EMPTY){
                    // capture
                    if (board->squares [iIndex][jIndex] > EMPTY){
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        temp.capture = TRUE;
                        addMove(&blackKnightMoves,temp);
                    }
                    else{
                        Move temp;
                        temp.startSquare = i*8 + j;
                        temp.targetSquare = iIndex*8 + jIndex;
                        addMove(&blackKnightMoves,temp);
                    }
                }
            }
        }
    }
    return blackKnightMoves;
}

int main(){
    Board board;
    printf("Enter a FEN string: ");
    char string[100];
    scanf("%s",string);
    readFenIntoBoard(&board,string);
    printBoard(&board);
    printf("legal moves :\n");
    MoveList whiteRookMoves = legalWhiteKnightMoves(&board);
    for (int k = 0;k<whiteRookMoves.count;k++){
        printf("start square: %d\ttargetSquare: %d\n",whiteRookMoves.moves[k].startSquare, whiteRookMoves.moves[k].targetSquare);
    }
    return 0;
}