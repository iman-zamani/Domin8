#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "move.h"
#include "board.h"
void main(){

    // initialize the board 
    Board* board = create_board();
    print_chess_board(board);
    return ;
}