#include "Block.h"

Block::Block()
    : m_Color(NONE), m_Piece(EMPTY)
{
    LogDebug (BIT_BLOCK, "Block::Block(), Block Constructor Called ... \n");
}

Block::~Block()
{
    LogDebug (BIT_BLOCK, "Block::~Block(), Block Destructor Called ... \n");
}

void Block::SetBlockColor(const Color_e color)
{
    LogInfo(BIT_BLOCK, " Block::SetBlockColor(), Block Color is Set to %d \n", color);
    m_Color = color;
}

void Block::SetBlockPiece(const Piece_e piece)
{
    LogInfo(BIT_BLOCK, " Block::SetBlockColor(), Block Piece is Set to %d \n", piece);
    m_Piece = piece;
}

void Block::ResetBlock()
{
    SetBlockColor(NONE);
    SetBlockPiece(EMPTY);
}

void Block::SetBlock(Color_e color, Piece_e piece)
{
    SetBlockColor(color);
    SetBlockPiece(piece);
}

Color_e Block::GetBlockColor() const
{
    return m_Color;
}

Piece_e Block::GetBlockPiece() const
{
    return m_Piece;
}