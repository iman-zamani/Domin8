#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "log.h"
#include "move.h"


uint64_t position_to_bitboard(int position){
    uint64_t ret = 1ULL << position;
    return ret;
}
Board* create_board_from_fen(const char* FEN){
    Board* ret = calloc(1,sizeof(Board));
    int i=0, j=56;
    while(FEN[i] != ' ' && j >= 0){
        if (FEN[i] == '/'){
            j-= 16;
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
                ret->bishop_b |= temp;
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
                ret->bishop_w |= temp;
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
    ret->short_castle_available_for_white = false;
    ret->short_castle_available_for_black = false;
    ret->long_castle_available_for_white = false;
    ret->long_castle_available_for_black = false;
    while(FEN[i] != ' '){
        if(FEN[i] == 'K'){
            ret->short_castle_available_for_white = true;
        }
        else if(FEN[i] == 'Q'){
            ret->long_castle_available_for_white = true;
        }
        else if(FEN[i] == 'k'){
            ret->short_castle_available_for_black = true;
        }
        else if(FEN[i] == 'q'){
            ret->long_castle_available_for_black = true;
        }
        i++;
    }
    i++;
    // things that are left to add
    // 1) if en passant is available what pawn moved ?
    // 2) number of half moves from the last capture or pawn moement
    // 3) number of half moves
    return ret;
}
Board* create_board_starting_position(){
    const char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    return create_board_from_fen(FEN);
}

void print_board(Board* board){
    for(int i=56;i>=0;i++){
        uint64_t temp = 1ULL << i;
        if(board->pawn_w & temp){
            printf("P ");
        }
        else if(board->rook_w & temp){
            printf("R ");
        }
        else if(board->knight_w & temp){
            printf("N ");
        }
        else if(board->bishop_w & temp){
            printf("B ");
        }
        else if(board->queen_w & temp){
            printf("Q ");
        }
        else if(board->king_w & temp){
            printf("K ");
        }
        else if(board->pawn_b & temp){
            printf("p ");
        }
        else if(board->rook_b & temp){
            printf("r ");
        }
        else if(board->knight_b & temp){
            printf("n ");
        }
        else if(board->bishop_b & temp){
            printf("b ");
        }
        else if(board->queen_b & temp){
            printf("q ");
        }
        else if(board->king_b & temp){
            printf("k ");
        }
        else {
            printf("  ");
        }
        if ((i+1) % 8 == 0){
            i -= 16;
            printf("\n");
        }
    }

}
