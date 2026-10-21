#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "move.h"
#include "board.h"
int main(){
    Board* board = create_board_from_fen("rnbq1b1r/p1pppkpp/5p1n/1p6/4P3/2P2N2/PP1PBPPP/RNBQK2R w KQ - 1 5");
    print_board(board);
    free(board);
    return 0;
}
