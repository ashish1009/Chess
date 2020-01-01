#include "Chess.h"

bool Chess::MoveKnight(unsigned short dstX, unsigned short dstY)
{
    const unsigned short playerIndex = GetPlayerIdx();
    const unsigned short oppPlayerIndex = GetOppPlayerIdx();

    const Position_s &src = m_Player[playerIndex].GetPlayerSource();

    m_bDestinationValidity = (((2 == abs(dstY - src.Y)) && (1 == abs(dstX - src.X))) || ((1 == abs(dstY - src.Y)) && (2 == abs(dstX - src.X))));
    
    if (m_Block[dstX][dstY].GetBlockColor() == m_Player[oppPlayerIndex].GetPlayerColor())
    {
        if (KING == m_Block[dstX][dstY].GetBlockPiece())
        {
            m_bGameOver = true;
        }
        m_Player[playerIndex].SetCutPiece(m_Block[dstX][dstY].GetBlockPiece());
    }

    if (m_bDestinationValidity)
    {
        SetDstBlock(dstX, dstY, m_Block[src.X][src.Y]);
        ResetSrcBlock(src.X, src.Y);
    }
    return m_bDestinationValidity;
}