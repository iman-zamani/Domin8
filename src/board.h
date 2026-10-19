#pragma once
#include "move.h"
#include <stdint.h>

#define WHITE 'W'
#define BLACK 'B'
struct{
    // bitboard positions
    uint64_t pawn_w;
    uint64_t pawn_b;
    uint64_t rook_w;
    uint64_t rook_b;
    uint64_t knight_w;
    uint64_t knight_b;
    uint64_t biship_w;
    uint64_t biship_b;
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
    move last_played;
    // whos turn it is (W white and B black)
    char whos_turn_it_is;
}typedef Board ;
