#pragma once



#define PAWN_W 1
#define PAWN_B -1
#define ROOK_W 5
#define ROOK_B -5
#define KNIGHT_W 3
#define KNIGHT_B -3
#define BISHIP_W 4
#define BISHOP_B -4
#define KING_W 20
#define KING_B -20
#define QUEEN_W 10
#define QUEEN_B -10

#define EN_PASSANT 'E'
#define SHORT_CASTLE 'S'
#define LONG_CASTLE 'L'
#define PROMOT_TO_QUEEN 'Q'
#define PROMOT_TO_BISHOP 'B'
#define PROMOT_TO_KNIGHT 'N'
#define PROMOT_TO_ROOK 'R'

// piece position index based on location
// 56 57 58 59 60 61 62 63
// 48 49 50 51 52 53 54 55
// 40 41 42 43 44 45 46 47
// 32 33 34 35 36 37 38 39
// 24 25 26 27 28 29 30 31
// 16 17 18 19 20 21 22 23
// 08 09 10 11 12 13 14 15
// 00 01 02 03 04 05 06 07
// starter position
// r n b q k b n r
// p p p p p p p p
// . . . . . . . .
// . . . . . . . .
// . . . . . . . .
// . . . . . . . .
// P P P P P P P P
// R N B Q K B N R
struct{
    int start_sqaure;
    int end_sqaure;
    int piece_type;
    // special moves like short castle, long castle, En passant and promotions
    // En passant --> E
    // short castle --> S
    // long catle --> L
    // queen promotion --> Q
    // knight promotion --> N
    // bishop promotion --> B
    // rook promotion --> R
    char special_move;
}typedef move ;
