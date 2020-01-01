#pragma once

enum FileBitMask_e
{
    /* first Nibble (LSB) */
    BIT_MAIN = 0,
    BIT_CHESS,
    BIT_BLOCK,
    BIT_PlAYER,
    
    /* second Nibble */
    BIT_KING,
    BIT_QUEEN,
    BIT_ROOK,
    BIT_BISHOP,

    /* third Nibble */
    BIT_KNIGHT,
    BIT_PAWN,

    BIT_DEFAULT

};