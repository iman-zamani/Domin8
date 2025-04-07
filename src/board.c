#include <stdlib.h>
#include "define.h"
#include "move.h"
#include "board.h"
void readFenIntoBoard(Board * board ,char * FEN){
    int fenIndex = 0;
    bool exitLoop = FALSE;
    for (int i=0;i<8 && !exitLoop ;i++){
        for (int j=0;j<8 && !exitLoop;j++){
            char c = FEN[fenIndex];
            // exiting the loop 
            if (c == ' '){
                exitLoop = true;
                fenIndex++;
                break;
            }
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
    // whose turn is it to move 
    if (FEN[fenIndex] == 'w'){
        board->isWhiteTurn = TRUE;
    }
    else if (FEN[fenIndex] == 'b'){
        board->isWhiteTurn = FALSE;
    }
    else {
        fprintf(stderr,"ERROR: failed to read the fen string\n");
        exit(EXIT_FAILURE);
    }
    fenIndex++;
    if (FEN[fenIndex] != ' '){
        fprintf(stderr,"ERROR: failed to read the fen string\n");
        exit(EXIT_FAILURE);
    }
    // castling 
    board->blackLongCastle = FALSE;
    board->blackShortCastle = FALSE;
    board->whiteLongCastle = FALSE;
    board->whiteShortCastle = FALSE;
    while (FEN[++fenIndex]!= ' '){
        switch (FEN[fenIndex])
        {
        case 'K':
            board->whiteShortCastle = TRUE;
            break;
        case 'Q':
            board->whiteLongCastle = TRUE;
            break;
        case 'k':
            board->blackShortCastle = TRUE;
            break;
        case 'q':
            board->blackLongCastle = TRUE;
            break;
        default:
            fprintf(stderr,"ERROR: failed to read the fen string\n");
            exit(EXIT_FAILURE);
            break;
        }
    }
    // en passant
    if (FEN[fenIndex + 1] == '-') {
        board->targetEnPassantSquare = -1; 
        fenIndex+=2;
    } else {
        int jIndex =  FEN[++fenIndex] - 'a';       
        int iIndex = '8' - FEN[++fenIndex] ;
        board->targetEnPassantSquare = iIndex * 8 + jIndex;
    }
    board->halfMovesFromLastCaptureOrPawnMove = 0;
    while (FEN[++fenIndex] != ' '){
        if (FEN[fenIndex] < '0' || FEN[fenIndex] > '9') break;
        board->halfMovesFromLastCaptureOrPawnMove = 
        board->halfMovesFromLastCaptureOrPawnMove * 10 + (FEN[fenIndex] - '0');
    }
    board->numFullMoves = 0;
    while (FEN[++fenIndex] != '\0'){
        if (FEN[fenIndex] < '0' || FEN[fenIndex] > '9') break;
        board->numFullMoves = 
        board->numFullMoves * 10 + (FEN[fenIndex] - '0');
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
bool boardIsCheck(Board *board){

    int king = EMPTY;
    int rook = EMPTY;
    int queen = EMPTY;
    int bishop = EMPTY;
    int knight = EMPTY;
    int pawn = EMPTY;
    int relative = 1;
    if (board->isWhiteTurn){
        king = WHITE_KING;
        // they should be the opposite 
        rook = BLACK_ROOK;
        queen = BLACK_QUEEN;
        bishop = BLACK_BISHOP;
        knight = BLACK_KNIGHT;
        pawn = BLACK_PAWN;
    }
    else {
        king = BLACK_KING;
        // they should be the opposite 
        rook = WHITE_ROOK;
        queen = WHITE_QUEEN;
        bishop = WHITE_BISHOP;
        knight = WHITE_KNIGHT;
        pawn = WHITE_PAWN;
        relative = -1;
    }
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board->squares[i][j] == king){
                // sliding pieces ---------------------------------------------------------------------------------
                int iIndex = i;
                int jIndex = j;
                // how many we can go up 
                while(iIndex >0 && board->squares [UP][j] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == rook){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // how many we can go down 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && board->squares [DOWN][j] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == rook){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // how many we can go right 
                iIndex = i;
                jIndex = j;
                while(jIndex < 7 && board->squares [i][RIGHT] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == rook){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // how many we can go left 
                iIndex = i;
                jIndex = j;
                while(jIndex > 0 && board->squares [i][LEFT] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == rook){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // moves that are like bishop --------
                iIndex = i;
                jIndex = j;
                // how many we can go up right
                while(iIndex >0 && jIndex<7 && board->squares[UP][RIGHT] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == bishop){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // how many we can go down left
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex > 0 && board->squares [DOWN][LEFT] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == bishop){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // how many we can go down right 
                iIndex = i;
                jIndex = j;
                while(iIndex < 7 && jIndex < 7 && board->squares [DOWN][RIGHT] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == bishop){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // how many we can go up left 
                iIndex = i;
                jIndex = j;
                while(iIndex > 0 && jIndex > 0 && board->squares [UP][LEFT] * relative <= EMPTY){
                    if (board->squares [iIndex][jIndex] == queen || board->squares [iIndex][jIndex] == bishop){
                        return TRUE;
                    } 
                    else if (board->squares [iIndex][jIndex] * relative < EMPTY ){
                        break;
                    } 
                }
                // knight moves --------------------------------------------------------------------
                #define ONE [iIndex-=2][jIndex+=1]
                #define TWO [iIndex-=1][jIndex+=2]
                #define FOUR [iIndex+=1][jIndex+=2]
                #define FIVE [iIndex+=2][jIndex+=1]
                #define SEVEN [iIndex+=2][jIndex-=1]
                #define EIGHT [iIndex+=1][jIndex-=2]
                #define TEN [iIndex-=1][jIndex-=2]
                #define ELEVEN [iIndex-=2][jIndex-=1]

                iIndex = i;
                jIndex = j;
                
                // ------
                if(iIndex >1 && jIndex<7 && board->squares ONE == knight){
                    return TRUE;
                }
                // -------
                iIndex = i;
                jIndex = j;
                if(iIndex >0 && jIndex <6 && board->squares TWO == knight){
                    return TRUE;
                }
                // -----
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex < 6 && board->squares FOUR == knight){
                    return TRUE;
                }
                // --------
                iIndex = i;
                jIndex = j;
                if( iIndex<6 &&jIndex < 7 && board->squares FIVE == knight){
                    return TRUE;
                }
                // ---------------
                iIndex = i;
                jIndex = j;
                if(iIndex <6 && jIndex > 0 && board->squares SEVEN== knight){
                    return TRUE;
                }
                // ---------
                iIndex = i;
                jIndex = j;
                if(iIndex < 7 && jIndex > 1 && board->squares EIGHT == knight){
                    return TRUE;
                }
                // ------------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 0 && jIndex > 1 && board->squares TEN == knight){
                    return TRUE;
                }
                // ----------------
                iIndex = i;
                jIndex = j;
                if(iIndex > 1 && jIndex > 0 && board->squares ELEVEN == knight){
                    return TRUE;
                }
                // pawn checks ---------------------------------------------------------------------
                // white 
                if (board->isWhiteTurn && (board->squares[i-1][j-1] == pawn || board->squares[i-1][j+1] == pawn)){
                    return TRUE;
                }
                // black 
                if (!board->isWhiteTurn && (board->squares[i+1][j-1] == pawn || board->squares[i+1][j+1] == pawn)){
                    return TRUE;
                }
                return FALSE;
            }
        }
    }
    return FALSE;
}

// this function will apply any move to the board 
// it will not check if the move is legal or pseudoLegal
Board applyMove(Board* board, Move move){
    assert(!BIT_BOARD && "copying board in apply move function will be different now that we have bit boards");
    // the updated board to return  
    Board ret;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            ret.squares[i][j] = board->squares[i][j] ;
        }
    }
    ret.whiteShortCastle = board->whiteShortCastle;
    ret.whiteLongCastle = board->whiteLongCastle;
    ret.blackShortCastle = board->blackShortCastle;
    ret.blackLongCastle = board->blackLongCastle;
    ret.isWhiteTurn = !board->isWhiteTurn;
    ret.targetEnPassantSquare = -1;
    ret.halfMovesFromLastCaptureOrPawnMove = board->halfMovesFromLastCaptureOrPawnMove + 1;
    ret.numFullMoves = board->numFullMoves;
    if(!ret.isWhiteTurn) ret.numFullMoves++;
    //----------------------
    if (move.pawnMovingTwoSquares && move.pieceType>0){
        ret.targetEnPassantSquare = move.targetSquare +8;
    }
    if (move.pawnMovingTwoSquares && move.pieceType<0){
        ret.targetEnPassantSquare = move.targetSquare -8;
    }
    // if king moves 
    if (move.pieceType == WHITE_KING){
        ret.whiteShortCastle = FALSE;
        ret.whiteLongCastle = FALSE;
    }
    else if(move.pieceType == BLACK_KING){
        ret.blackShortCastle = FALSE;
        ret.blackLongCastle = FALSE;
    }
    // if rook moves white
    if (move.pieceType == WHITE_ROOK && move.startSquare == 63){
        ret.whiteShortCastle = FALSE;
    }
    else if (move.pieceType == WHITE_ROOK && move.startSquare == 56){
        ret.whiteLongCastle = FALSE;
    }
    // if rook moves black 
    if (move.pieceType == BLACK_ROOK && move.startSquare == 7){
        ret.blackShortCastle= FALSE;
    }
    else if (move.pieceType == BLACK_ROOK && move.startSquare == 0){
        ret.blackLongCastle = FALSE;
    }
    // if rook is captured 
    if (move.targetSquare == 63){
        ret.whiteShortCastle = FALSE;
    }
    else if (move.targetSquare == 56){
        ret.whiteLongCastle = FALSE;
    }
    // if rook moves black 
    if (move.targetSquare == 7){
        ret.blackShortCastle= FALSE;
    }
    else if (move.targetSquare == 0){
        ret.blackLongCastle = FALSE;
    }
    // we should add support for accessing the squares in a linear form instead of matrix 
    // apply the move itself 
    // if castle 
    if (move.shortCastle && move.pieceType > 0){
        ret.squares[move.startSquare] = EMPTY;
        ret.squares[move.targetSquare] = WHITE_KING;
        ret.squares[63] = EMPTY;
        ret.squares[61] = WHITE_ROOK;
    }
    else if (move.longCastle && move.pieceType > 0){
        ret.squares[move.startSquare] = EMPTY;
        ret.squares[move.targetSquare] = WHITE_KING;
        ret.squares[56] = EMPTY;
        ret.squares[59] = WHITE_ROOK;
    }
    else if (move.shortCastle && move.pieceType < 0){
        ret.squares[move.startSquare] = EMPTY;
        ret.squares[move.targetSquare] = BLACK_ROOK;
        ret.squares[7] = EMPTY;
        ret.squares[5] = BLACK_ROOK;
    }
    else if (move.longCastle && move.pieceType < 0){
        ret.squares[move.startSquare] = EMPTY;
        ret.squares[move.targetSquare] = BLACK_ROOK;
        ret.squares[0] = EMPTY;
        ret.squares[3] = BLACK_ROOK;
    }
    // en passant 
    if ((move.pieceType == WHITE_PAWN || move.pieceType == BLACK_PAWN )&& move.targetSquare == board->targetEnPassantSquare){
        ret.squares[move.startSquare] = EMPTY;
        ret.squares[move.targetSquare] = move.pieceType;
        if (move.pieceType > 0){
            ret.squares[move.targetSquare + 8] = EMPTY;
        }
        else {
            ret.squares[move.targetSquare - 8] = EMPTY;
        }
    }

    // other moves 
    ret.squares[move.startSquare] = EMPTY;
    ret.squares[move.targetSquare] = move.pieceType;
    return ret;
}