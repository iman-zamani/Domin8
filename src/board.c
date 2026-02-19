#include <stdio.h>
#include <stdlib.h>
#include "move.h"
#include "board.h"

Board* create_board(){
    Board* ret = (Board*)malloc(sizeof(Board));
    // set the flags
    ret->is_white_turn = TRUE; 
    ret->white_king_side_castle = TRUE; 
    ret->white_queen_side_castle = TRUE; 
    ret->black_king_side_castle = TRUE; 
    ret->black_queen_side_castle = TRUE;
    // no previous move or board
    ret->previous_move = NULL;
    ret->previous_board = NULL;
    // set the bit maps
    ret->white_rooks_bm = 0b0000000000000000000000000000000000000000000000000000000010000001;
    ret->white_bishops_bm = 0b0000000000000000000000000000000000000000000000000000000000100100;
    ret->white_knights_bm = 0b0000000000000000000000000000000000000000000000000000000001000010;
    ret->white_queens_bm = 0b0000000000000000000000000000000000000000000000000000000000010000;
    ret->white_king_bm = 0b0000000000000000000000000000000000000000000000000000000000001000;
    ret->white_pawns_bm = 0b0000000000000000000000000000000000000000000000001111111100000000;
    // black 
    ret->black_rooks_bm = 0b1000000100000000000000000000000000000000000000000000000000000000;
    ret->black_bishops_bm = 0b0010010000000000000000000000000000000000000000000000000000000000;
    ret->black_knights_bm = 0b0100001000000000000000000000000000000000000000000000000000000000;
    ret->black_queens_bm = 0b0001000000000000000000000000000000000000000000000000000000000000;
    ret->black_king_bm = 0b0000100000000000000000000000000000000000000000000000000000000000;
    ret->black_pawns_bm = 0b0000000011111111000000000000000000000000000000000000000000000000;
    // bitmap for the squares in control of sliding pieces, it should be set to zero in the standard starting position
    ret->white_sliding_attacks = 0;
    ret->black_sliding_attacks = 0;
    return ret;
}




bool is_nth_bit_set(uint64_t input, int8_t n){
    uint64_t i = 1ULL << n;
    return (input & i);
}
void print_chess_board(Board* board){
    for(int8_t i=63;i>=0;i--){
        if (is_nth_bit_set(board->white_rooks_bm,i)){
            printf("R ");
        }
        else if (is_nth_bit_set(board->white_knights_bm,i)){
            printf("N ");
        }
        else if (is_nth_bit_set(board->white_bishops_bm,i)){
            printf("B ");
        }
        else if (is_nth_bit_set(board->white_queens_bm,i)){
            printf("Q ");
        }
        else if (is_nth_bit_set(board->white_king_bm,i)){
            printf("K ");
        }
        else if (is_nth_bit_set(board->white_pawns_bm,i)){
            printf("P ");
        }
        else if (is_nth_bit_set(board->black_rooks_bm,i)){
            printf("r ");
        }
        else if (is_nth_bit_set(board->black_knights_bm,i)){
            printf("n ");
        }
        else if (is_nth_bit_set(board->black_bishops_bm,i)){
            printf("b ");
        }
        else if (is_nth_bit_set(board->black_queens_bm,i)){
            printf("q ");
        }
        else if (is_nth_bit_set(board->black_king_bm,i)){
            printf("k ");
        }
        else if (is_nth_bit_set(board->black_pawns_bm,i)){
            printf("p ");
        }
        else {
            printf("  ");
        }
        // -----
        if (i % 8 == 0){

            printf("\n");
        }
    }
}

uint8_t get_legal_white_pawn_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_black_pawn_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_white_rook_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_black_rook_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_white_bishop_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_black_bishop_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_white_queen_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_black_queen_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_white_king_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_black_king_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_white_knight_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_legal_black_knight_moves(Board *board, move* moves, uint8_t start_index);
uint8_t get_all_legal_white_moves(Board *board, move* moves){
    uint8_t start_index = 0;
    start_index = get_legal_white_pawn_moves(board, moves,start_index);
    start_index = get_legal_white_rook_moves(board, moves,start_index);
    start_index = get_legal_white_bishop_moves(board, moves,start_index);
    start_index = get_legal_white_queen_moves(board, moves,start_index);
    start_index = get_legal_white_king_moves(board, moves,start_index);
    start_index = get_legal_white_knight_moves(board, moves,start_index);
    return start_index;
}
uint8_t get_all_legal_black_moves(Board *board, move* moves){
    // start_index will tell the functions to where they should start filling moves in the array
    uint8_t start_index = 0;
    start_index = get_legal_black_pawn_moves(board, moves,start_index);
    start_index = get_legal_black_rook_moves(board, moves,start_index);
    start_index = get_legal_black_bishop_moves(board, moves,start_index);
    start_index = get_legal_black_queen_moves(board, moves,start_index);
    start_index = get_legal_black_king_moves(board, moves,start_index);
    start_index = get_legal_black_knight_moves(board, moves,start_index);
    return start_index;
}

move* get_legal_moves(Board* board){
    // maximum number of legal moves that can exist in a valid, legally reachable chess position is 218
    // we use calloc to make it easy for the program to detect empty indexes
    move * moves = (move*)calloc(219,sizeof(move));
    // number of legal moves we found in this position --> for freeing the rest (maybe)
    uint8_t moves_found = 0;
    if (moves == NULL) {
        perror("ERROR allocateing memory in get_legal_moves function\n");
        exit(EXIT_FAILURE);
    }
    if (board->is_white_turn){
        moves_found = get_all_legal_white_moves(board,moves);
    }
    else {
        moves_found = get_all_legal_black_moves(board,moves);
    }
    return moves;
}