#include "Chess.h"

bool Chess::MoveRook(unsigned short dstX, unsigned short dstY)
{
    const unsigned short playerIndex = GetPlayerIdx();
    const unsigned short oppPlayerIndex = GetOppPlayerIdx();

    const Position_s &src = m_Player[playerIndex].GetPlayerSource();

    m_bDestinationValidity = ((dstY == src.Y) ? MoveStraight(dstX, src.Y, src.X, 'X') : ((dstX == src.X) ? MoveStraight(dstY, src.X, src.Y, 'Y') : false));

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
