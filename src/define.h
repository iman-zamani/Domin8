#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// To Do List------------------
// add bit board for optimizing move generation 
#define BIT_BOARD  0
// optimize what move we should look first 
// for better alpha beta pruning
#define MOVE_ORDER 0
//----------------------------
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
