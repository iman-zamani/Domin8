#pragma once 
#include <stdbool.h>
#include <stdint.h>
#include "move.h"
struct {
    bool is_white_turn, white_king_side_castle, white_queen_side_castle, black_king_side_castle, black_queen_side_castle;
    move* previous_move;
    void* previous_board;
    // bit maps
    // white
    uint64_t white_rooks_bm;
    uint64_t white_bishops_bm;
    uint64_t white_knights_bm;
    uint64_t white_queens_bm;
    uint64_t white_king_bm;
    uint64_t white_pawns_bm;
    // black
    uint64_t black_rooks_bm;
    uint64_t black_bishops_bm;
    uint64_t black_knights_bm;
    uint64_t black_queens_bm;
    uint64_t black_king_bm;
    uint64_t black_pawns_bm;
}typedef Board;

Board* create_board();


bool is_nth_bit_set(uint64_t input, int8_t n); 
void print_chess_board(Board* board);

// the last pointer will be set to NULL 
move* get_legal_moves(Board* board);
move* get_legal_white_pawn_moves(Board *board);
move* get_legal_black_pawn_moves(Board *board);
move* get_legal_white_rook_moves(Board *board);
move* get_legal_black_rook_moves(Board *board);
move* get_legal_white_bishop_moves(Board *board);
move* get_legal_black_bishop_moves(Board *board);
move* get_legal_white_queen_moves(Board *board);
move* get_legal_black_queen_moves(Board *board);
move* get_legal_white_king_moves(Board *board);
move* get_legal_black_king_moves(Board *board);
move* get_legal_white_knight_moves(Board *board);
move* get_legal_black_knight_moves(Board *board);
move* all_legal_white_moves(Board *board);
move* all_legal_black_moves(Board *board);