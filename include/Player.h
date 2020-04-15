#pragma once

#include <iostream>
#include "Common.h"

/*
 * Struct
 */
struct Position_s
{
    unsigned short X;
    unsigned short Y;

    Position_s()
        : X(0), Y(0) {}
};

/*
 * Class
 */
class Player
{
private:
    static const unsigned short MAX_PIECES = 16;

private:
    std::string m_Name;
    Color_e m_Color;
    Piece_e m_CutPieces[MAX_PIECES];

    Position_s m_Source;

    Piece_e m_SourcePiece;
    unsigned short m_NumCutPiece;

private:
    void SetPlayerName(const std::string &name);
    void SetPlayerColor(const Color_e color);
    void SetSourcePiece(Piece_e piece);

    void SetCutPiece(Piece_e piece);

    std::string GetPlayerName() const;
    Color_e GetPlayerColor() const;
    Piece_e GetSourcePiece() const;

    Position_s GetPlayerSource() const;

    void Reset();

public:
    Player();
    ~Player();

public:
    friend class Chess;
};
