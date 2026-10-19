#include <stdlib.h>
#include "board.h"
#define TRUE 1
#define FALSE 0


uint64_t position_to_bitboard(int position){
    uint64_t ret = 1 << position;
    return ret;
}
Board* create_board_from_fen(const char* FEN){
    Board* ret = malloc(sizeof(Board));
    int i=0, j=56;
    while(FEN[i] != ' ' && j >= 0){
        if (FEN[i] == '/'){
            j-= 15;
            i++;
            continue;
        }
        if (FEN[i] > '0' && FEN[i] < '9' ){
            j+= FEN[i] - '0';
            i++;
            continue;
        }
        uint64_t temp = position_to_bitboard(j);
        switch (FEN[i]) {
            case 'p':
                ret->pawn_b |= temp;
                ret->pieces_b |= temp;
                break;
            case 'b':
                ret->biship_b |= temp;
                ret->pieces_b |= temp;
                break;
            case 'n':
                ret->knight_b |= temp;
                ret->pieces_b |= temp;
                break;
            case 'q':
                ret->queen_b |= temp;
                ret->pieces_b |= temp;
                break;
            case 'k':
                ret->king_b |= temp;
                ret->pieces_b |= temp;
                break;
            case 'r':
                ret->rook_b |= temp;
                ret->pieces_b |= temp;
                break;
            case 'P':
                ret->pawn_w |= temp;
                ret->pieces_w |= temp;
                break;
            case 'B':
                ret->biship_w |= temp;
                ret->pieces_w |= temp;
                break;
            case 'N':
                ret->knight_w |= temp;
                ret->pieces_w |= temp;
                break;
            case 'Q':
                ret->queen_w |= temp;
                ret->pieces_w |= temp;
                break;
            case 'K':
                ret->king_w |= temp;
                ret->pieces_w |= temp;
                break;
            case 'R':
                ret->rook_w |= temp;
                ret->pieces_w |= temp;
                break;

        }
        i++,j++;
    }
    i++;
    if (FEN[i] == 'w'){
        ret->whos_turn_it_is = WHITE;
    }
    else{
        ret->whos_turn_it_is = BLACK;
    }
    i+=2;
    ret->short_castle_availbe_for_white = FALSE;
    ret->short_castle_availbe_for_black = FALSE;
    ret->long_castle_availbe_for_white = FALSE;
    ret->long_castle_availbe_for_black = FALSE;
    while(FEN[i] != ' '){
        if(FEN[i] == 'K'){
            ret->short_castle_availbe_for_white = TRUE;
        }
        else if(FEN[i] == 'Q'){
            ret->long_castle_availbe_for_white = TRUE;
        }
        else if(FEN[i] == 'k'){
            ret->short_castle_availbe_for_black = TRUE;
        }
        else if(FEN[i] == 'q'){
            ret->long_castle_availbe_for_black = TRUE;
        }
        i++;
    }
    i++;
    // things that are left to add
    // 1) if en passant is availbe what pawn moved ?
    // 2) number of half moves from the last capture or pawn moement
    // 3) number of half moves
    return ret;
}
Board* create_board_starting_position(){
    const char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
     return create_board_from_fen(FEN);
}
