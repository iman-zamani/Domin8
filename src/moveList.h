#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "board.h"
#include "move.h"
typedef struct{
    int count;     // how many moves are stored
    int capacity;  // total allocated number of moves we can have 
    Move* moves;
} MoveList;

void initMoveList(MoveList * list);
void ensureMoveCapacity(MoveList* list);
void addMove(MoveList* list, Move move);

