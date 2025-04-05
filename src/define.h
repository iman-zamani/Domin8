#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
