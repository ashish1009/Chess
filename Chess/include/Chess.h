#pragma once

#include <iostream>
#include <vector>
#include "Block.h"
#include "Player.h"
#include "Common.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const std::string gChessPath = "/Users/ashish./Documents/XCode/Chess/Chess/images/";

/*
 * Chess Class
 */
class Chess
{
private:
    /*
    * Private Enum
    */
    enum FirstPos_e
    {
        ROOK_1_FIRST_POS = 0,
        KNIGHT_1_FIRST_POS = 1,
        BISHOP_1_FIRST_POS = 2,
        QUEEN_FIRST_POS = 3,
        KING_FIRST_POS = 4,
        BISHOP_2_FIRST_POS = 5,
        KNIGHT_2_FIRST_POS = 6,
        ROOK_2_FIRST_POS = 7,
    };

    /*
    * Private Const Members
    */    
    static const unsigned short BOARD_HEIGHT = 800;
    static const unsigned short BOARD_WIDTH = 1500;

    static const unsigned short CHESS_SIZE = 790;

    static const unsigned short BLOCK_SIZE = 99;

    static const unsigned short FONT_SIZE = 20;
    static const unsigned short BLACK_OFFSET = 20;
    static const unsigned short WHITE_OFFSET = 40;

    static const unsigned short CUT_X_OFFSET = CHESS_SIZE + 10;
    static const unsigned short BLACK_CUT_Y_OFFSET_1 = BLACK_OFFSET + 40;
    static const unsigned short BLACK_CUT_Y_OFFSET_2 = BLACK_OFFSET + 80;

    static const unsigned short WHITE_CUT_Y_OFFSET_1 = CHESS_SIZE - WHITE_OFFSET - 40;
    static const unsigned short WHITE_CUT_Y_OFFSET_2 = CHESS_SIZE - WHITE_OFFSET - 80;

    static const short PAWN_POS = 15;
    static const short BLACK_ROOK_POS = -8;
    static const short BLACK_BISHOP_POS = 10;
    static const short BLACK_KNIGHT_POS = 5;
    static const short BLACK_KING_POS = 5;
    static const short BLACK_QUEEN_POS = 10;

    static const short WHITE_ROOK_POS = 15;
    static const short WHITE_BISHOP_POS = -8;
    static const short WHITE_KNIGHT_POS = 13;
    static const short WHITE_KING_POS = 0;
    static const short WHITE_QUEEN_POS = 10;

    static const unsigned short CHESS_ROW = 8;
    static const unsigned short CHESS_COL = 8;

    static const unsigned short BLACK_ROW_1 = 0; // Consider as First Row from Top
    static const unsigned short BLACK_ROW_2 = 1;
    static const unsigned short WHITE_ROW_1 = 7; // Consider as Last Row from Top
    static const unsigned short WHITE_ROW_2 = 6;

    static const unsigned short MAX_PLAYER = 2;

    static const bool PLAYER_1 = 0;
    static const bool PLAYER_2 = 1;

    static const short PLUS_ONE = 1;
    static const short MINUS_ONE = -1;

private:
    sf::Texture m_ChessTexture;
    sf::Texture m_BlackPawnTexture;
    sf::Texture m_BlackRookTexture;
    sf::Texture m_BlackBishopTexture;
    sf::Texture m_BlackKnightTexture;
    sf::Texture m_BlackKingTexture;
    sf::Texture m_BlackQueenTexture;

    sf::Texture m_WhitePawnTexture;
    sf::Texture m_WhiteRookTexture;
    sf::Texture m_WhiteBishopTexture;
    sf::Texture m_WhiteKnightTexture;
    sf::Texture m_WhiteKingTexture;
    sf::Texture m_WhiteQueenTexture;

    sf::Texture m_BlackPawnTextureCut;
    sf::Texture m_BlackRookTextureCut;
    sf::Texture m_BlackBishopTextureCut;
    sf::Texture m_BlackKnightTextureCut;
    sf::Texture m_BlackKingTextureCut;
    sf::Texture m_BlackQueenTextureCut;

    sf::Texture m_WhitePawnTextureCut;
    sf::Texture m_WhiteRookTextureCut;
    sf::Texture m_WhiteBishopTextureCut;
    sf::Texture m_WhiteKnightTextureCut;
    sf::Texture m_WhiteKingTextureCut;
    sf::Texture m_WhiteQueenTextureCut;

    sf::Texture m_WoodenBackGroundTexture;

    sf::Texture m_CursorBlockTexture;
    sf::Texture m_SelectedBlockTexture;

    sf::Font m_Font;

private:
    Block m_Block[CHESS_ROW][CHESS_COL];
    Player m_Player[MAX_PLAYER];

    Color_e m_Turn;

    bool m_bGameOver;
    bool m_bSourceValidity;
    bool m_bDestinationValidity;
    bool m_bIsSourceSelected;

    std::vector<bool (Chess::*)(unsigned short, unsigned short)> m_MovePieceFnPtr;

private:
    void InitChess();
    void SetChessColor(const unsigned short rowIdx, const unsigned short colIdx);
    void SetChessPiece(const unsigned short rowIdx, const unsigned short colIdx);

    void PrintChess();

    void GetPlayerInfo();

    void ResetSrcBlock(const unsigned short X, const unsigned short Y);
    void SetDstBlock(const unsigned short X, const unsigned short Y, const Block &block);

    bool IsSourceValid(const unsigned short X, const unsigned short Y);
    bool IsDestinationValid(const unsigned short X, const unsigned short Y, bool (Chess::*)(unsigned short, unsigned short));

    void ToggleTurn();

    void ResetGame();

private:
    unsigned short GetPlayerIdx() const;
    unsigned short GetOppPlayerIdx() const;

private:
    bool MoveDefault(unsigned short X, unsigned short Y);
    bool MoveKing(unsigned short X, unsigned short Y);
    bool MoveQueen(unsigned short X, unsigned short Y);
    bool MoveBishop(unsigned short X, unsigned short Y);
    bool MoveRook(unsigned short X, unsigned short Y);
    bool MoveKnight(unsigned short X, unsigned short Y);
    bool MovePawn(const unsigned short X, const unsigned short Y);

    bool MoveStraight(const unsigned short dst, const unsigned short otherCoordinate, const unsigned short src, const char direction);
    bool MoveDiagonal(const unsigned short dstY, const unsigned short dstX, const unsigned short srcY, const unsigned short srcX);

private:
    int GetTextures();

public:
    int PlayGame();

public:
    Chess();
    ~Chess();
};
