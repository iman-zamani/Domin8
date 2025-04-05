#pragma once 
typedef struct{
    int count;     // how many moves are stored
    int capacity;  // total allocated number of moves we can have 
    Move* moves;
} MoveList;

void initMoveList(MoveList * list);
void ensureMoveCapacity(MoveList* list);
void addMove(MoveList* list, Move move);

