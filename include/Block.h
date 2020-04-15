#pragma once

#include <iostream>
#include "Common.h"

/*
 * Block Class
 */
class Block
{
private:
    Color_e m_Color;
    Piece_e m_Piece;

public:
    void SetBlockColor(const Color_e color);
    void SetBlockPiece(const Piece_e piece);

    void ResetBlock();
    void SetBlock(const Color_e color, Piece_e piece);

    Color_e GetBlockColor() const;
    Piece_e GetBlockPiece() const;
    
public:
    Block();
    ~Block();
};
