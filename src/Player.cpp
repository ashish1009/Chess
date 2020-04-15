#include "Player.h"
#include <string>

Player::Player()
    : m_Name("Player Name"), m_Color(NONE), m_SourcePiece(PAWN)
{
    LogDebug(BIT_PlAYER, "Player::Player(), Player Constructor called ... \n");
    for (unsigned short idx = 0; idx < MAX_PIECES; idx++)
    {
        m_CutPieces[idx] = EMPTY;
    }
}

void Player::Reset()
{
    m_SourcePiece = EMPTY;
    
    m_Source.X = 0;
    m_Source.Y = 0;

    m_NumCutPiece = 0;

    for (unsigned short idx = 0; idx < MAX_PIECES; idx++)
    {
        m_CutPieces[idx] = EMPTY;
    }
}

Player::~Player() 
{
    LogDebug(BIT_PlAYER, "Player::Player(), Player Destructor called ... \n");
}

void Player::SetPlayerName(const std::string &name)
{
    m_Name = name;
}

std::string Player::GetPlayerName() const
{
    return m_Name;
}

Color_e Player::GetPlayerColor() const
{
    return m_Color;
}

Piece_e Player::GetSourcePiece() const
{
    return m_SourcePiece;
}

Position_s Player::GetPlayerSource() const
{
    return m_Source;
}

void Player::SetSourcePiece(Piece_e piece)
{
    m_SourcePiece = piece;
}

void Player::SetPlayerColor(const Color_e color)
{
    m_Color = color;
}

void Player::SetCutPiece(Piece_e piece)
{
    m_CutPieces[m_NumCutPiece] = piece;
    m_NumCutPiece++;
}