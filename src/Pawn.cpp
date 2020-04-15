#include "Chess.h"

#define BLACK_DST 0
#define WHITE_DST 7

bool Chess::MovePawn(const unsigned short dstX, const unsigned short dstY)
{
    const unsigned short playerIndex = GetPlayerIdx();
    const unsigned short oppPlayerIndex = GetOppPlayerIdx();

    const Position_s &src = m_Player[playerIndex].GetPlayerSource();
    const Color_e playerColor = m_Player[playerIndex].GetPlayerColor();
    const short validDistanceX = (BLACK == playerColor) ? PLUS_ONE : MINUS_ONE;

    if (validDistanceX == (dstX - src.X))
    {
        if (m_Player[oppPlayerIndex].GetPlayerColor() == m_Block[dstX][dstY].GetBlockColor())
        {
            if (PLUS_ONE == abs(dstY - src.Y))
            {
                if (KING == m_Block[dstX][dstY].GetBlockPiece())
                {
                    m_bGameOver = true;
                }
                m_Player[playerIndex].SetCutPiece(m_Block[dstX][dstY].GetBlockPiece());
                m_bDestinationValidity = true;
            }
        }
        else
        {
            if (dstY == src.Y)
            {
                m_bDestinationValidity = true;
            }
        }
    }
    if (m_bDestinationValidity)
    {
        SetDstBlock(dstX, dstY, m_Block[src.X][src.Y]);
        ResetSrcBlock(src.X, src.Y);

        if ((!m_bGameOver)&&(((playerColor == WHITE) && (BLACK_DST == dstX)) || ((playerColor == BLACK) && (WHITE_DST == dstX))))
        {
        }
    }

    return m_bDestinationValidity;
}