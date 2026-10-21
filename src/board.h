#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "move.h"

#define WHITE 'W'
#define BLACK 'B'
typedef struct{
    // bitboard positions
    uint64_t pawn_w;
    uint64_t pawn_b;
    uint64_t rook_w;
    uint64_t rook_b;
    uint64_t knight_w;
    uint64_t knight_b;
    uint64_t bishop_w;
    uint64_t bishop_b;
    uint64_t queen_w;
    uint64_t queen_b;
    uint64_t king_w;
    uint64_t king_b;
    // bitboard for colors
    uint64_t pieces_w;
    uint64_t pieces_b;
    // bitboard for controlled squares
    uint64_t controlled_w;
    uint64_t controlled_b;
    // last played move
    Move last_played;
    // whos turn it is (W white and B black)
    char whos_turn_it_is;
    // if castles are available
    bool short_castle_available_for_white;
    bool short_castle_available_for_black;
    bool long_castle_available_for_white;
    bool long_castle_available_for_black;
} Board ;


Board* create_board_from_fen(const char* FEN);
Board* create_board_starting_position();
uint64_t position_to_bitboard(int position);

void print_board(Board* board);
