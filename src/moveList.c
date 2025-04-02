#include "moveList.h"
void initMoveList(MoveList * list){
    list->count = 0;
    list->capacity = 32;
    list->moves = NULL;
    list->moves = (Move*)malloc(list->capacity * sizeof(Move));  
    if (!list->moves) {
        perror("Memory allocation failed list moves");
        exit(EXIT_FAILURE);
    }
}
void ensureMoveCapacity(MoveList* list) {
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        if (new_capacity == 0) new_capacity = 32;  
        Move* temp = (Move*)realloc(list->moves, new_capacity * sizeof(Move));
        if (temp != NULL) {
            list->moves = temp;
            list->capacity = new_capacity;
        } 
        else {
            perror("Failed to realloc memory in ensureMoveCapacity function");
            exit(EXIT_FAILURE);
        }
    }
}
void addMove(MoveList* list, Move move) {
    ensureMoveCapacity(list);
    list->moves[list->count++] = move;
}