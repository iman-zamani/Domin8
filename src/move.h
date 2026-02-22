#pragma once 
#include <stdbool.h>
// for bool
#define TRUE 1
#define FALSE 0
// while pieces 
#define WHITE_PAWN 1
#define WHITE_BISHOP 4
#define WHITE_KNIGHT 3
#define WHITE_KING 20
#define WHITE_QUEEN 10
#define WHITE_ROOK 5
// black pieces
#define BLACK_PAWN -1
#define BLACK_BISHOP -4
#define BLACK_KNIGHT -3
#define BLACK_KING -20
#define BLACK_QUEEN -10
#define BLACK_ROOK -5
struct {
    int8_t start_square;
    int8_t dest_square;
    int8_t piece_type;
}typedef move;