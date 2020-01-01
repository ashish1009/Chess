#pragma once
#include "Logger.h"
#include "FileBitMask.h"

#define LogDebug(bitMask, ...) Logger::GetLoggerInstance()->LOG(LOG_DEBUG, bitMask, __VA_ARGS__ )
#define LogInfo(bitMask, ...) Logger::GetLoggerInstance()->LOG(LOG_INFO, bitMask, __VA_ARGS__ )
#define LogWarning(bitMask, ...) Logger::GetLoggerInstance()->LOG(LOG_WARNING, bitMask, __VA_ARGS__ )
#define LogError(bitMask, ...) Logger::GetLoggerInstance()->LOG(LOG_ERROR, bitMask, __VA_ARGS__ )

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