#include "Chess.h"

bool Chess::MoveStraight(const unsigned short dst, const unsigned short otherCoordinate, const unsigned short src, const char direction)
{
    unsigned short moveDst = dst;
    const short moveStep = (src < dst) ? PLUS_ONE : MINUS_ONE;
    while (moveDst != src)
    {
        moveDst -= moveStep;
        if (moveDst == src)
        {
            return true;
        }
        if ('X' == direction)
        {
            if (EMPTY != m_Block[moveDst][otherCoordinate].GetBlockPiece())
            {
                return false;
            }
        }
        else if ('Y' == direction)
        {
            if (EMPTY != m_Block[otherCoordinate][moveDst].GetBlockPiece())
            {
                return false;
            }
        }
    }
    return false;
}

bool Chess::MoveDiagonal(const unsigned short dstY, const unsigned short dstX, const unsigned short srcY, const unsigned short srcX)
{
    unsigned short moveDstX = dstX;
    unsigned short moveDstY = dstY;

    const short moveStepX = (srcX < dstX) ? PLUS_ONE : MINUS_ONE;
    const short moveStepY = (srcY < dstY) ? PLUS_ONE : MINUS_ONE;

    if ((abs(dstY - srcY)) == (abs(dstX - srcX)))
    {
        while ((moveDstX != srcX) && (moveDstY != srcY))
        {
            moveDstY -= moveStepY;
            moveDstX -= moveStepX;

            if ((moveDstY == srcY) || (moveDstX == srcX))
            {
                return true;
            }

            if (m_Block[moveDstX][moveDstY].GetBlockPiece() != EMPTY)
            {
                return false;
            }
        }
    }
    return false;
}