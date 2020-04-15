#pragma once
#include "Logger.h"
#include "FileBitMask.h"

/*
 * Enums
 */
enum Piece_e : unsigned short
{
    EMPTY = 0,
    KING = 1,
    QUEEN = 2,
    BISHOP = 3,
    ROOK = 4,
    KNIGHT = 5,
    PAWN = 6
};

enum Color_e : short
{
    NONE = -1,
    BLACK = 0,
    WHITE = 1
};