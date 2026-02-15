#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "move.h"
#include "board.h"
bool is_nth_bit_set(uint64_t input, int n){
    uint64_t i = 1ULL << n;
    return (input & i);
}
void print_chess_board(Board* board){
    for(int i=63;i>=0;i--){
        if (is_nth_bit_set(board->white_rooks_bm,i)){
            printf("R ");
        }
        else if (is_nth_bit_set(board->white_knights_bm,i)){
            printf("N ");
        }
        else if (is_nth_bit_set(board->white_bishops_bm,i)){
            printf("B ");
        }
        else if (is_nth_bit_set(board->white_queens_bm,i)){
            printf("Q ");
        }
        else if (is_nth_bit_set(board->white_king_bm,i)){
            printf("K ");
        }
        else if (is_nth_bit_set(board->white_pawns_bm,i)){
            printf("P ");
        }
        else if (is_nth_bit_set(board->black_rooks_bm,i)){
            printf("r ");
        }
        else if (is_nth_bit_set(board->black_knights_bm,i)){
            printf("n ");
        }
        else if (is_nth_bit_set(board->black_bishops_bm,i)){
            printf("b ");
        }
        else if (is_nth_bit_set(board->black_queens_bm,i)){
            printf("q ");
        }
        else if (is_nth_bit_set(board->black_king_bm,i)){
            printf("k ");
        }
        else if (is_nth_bit_set(board->black_pawns_bm,i)){
            printf("p ");
        }
        else {
            printf("  ");
        }
        // -----
        if (i % 8 == 0){

            printf("\n");
        }
    }
}
int main(){

    // initialize the board 
    Board* board = create_board();
    print_chess_board(board);
    return 0;
}