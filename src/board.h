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