#include "Chess.h"

void Chess::InitChess()
{
    for (unsigned short rowIdx = 0; rowIdx < CHESS_ROW; rowIdx++)
    {
        for (unsigned short colIdx = 0; colIdx < CHESS_COL; colIdx++)
        {
            SetChessColor(rowIdx, colIdx);
            SetChessPiece(rowIdx, colIdx);
        }
    }

    m_MovePieceFnPtr.push_back(&Chess::MoveDefault);
    m_MovePieceFnPtr.push_back(&Chess::MoveKing);
    m_MovePieceFnPtr.push_back(&Chess::MoveQueen);
    m_MovePieceFnPtr.push_back(&Chess::MoveBishop);
    m_MovePieceFnPtr.push_back(&Chess::MoveRook);
    m_MovePieceFnPtr.push_back(&Chess::MoveKnight);
    m_MovePieceFnPtr.push_back(&Chess::MovePawn);
}

void Chess::SetChessColor(const unsigned short rowIdx, const unsigned short colIdx)
{
    if ((BLACK_ROW_1 == rowIdx) || (BLACK_ROW_2 == rowIdx))
    {
        m_Block[rowIdx][colIdx].SetBlockColor(BLACK);
    }
    else if ((WHITE_ROW_1 == rowIdx) || (WHITE_ROW_2 == rowIdx))
    {
        m_Block[rowIdx][colIdx].SetBlockColor(WHITE);
    }
    else
    {
        m_Block[rowIdx][colIdx].SetBlockColor(NONE);
    }
}

void Chess::SetChessPiece(const unsigned short rowIdx, const unsigned short colIdx)
{
    if ((BLACK_ROW_1 == rowIdx) || (WHITE_ROW_1 == rowIdx))
    {
        if ((ROOK_1_FIRST_POS == colIdx) || (ROOK_2_FIRST_POS == colIdx))
        {
            m_Block[rowIdx][colIdx].SetBlockPiece(ROOK);
        }
        else if ((KNIGHT_1_FIRST_POS == colIdx) || (KNIGHT_2_FIRST_POS == colIdx))
        {
            m_Block[rowIdx][colIdx].SetBlockPiece(KNIGHT);
        }
        else if ((BISHOP_1_FIRST_POS == colIdx) || (BISHOP_2_FIRST_POS == colIdx))
        {
            m_Block[rowIdx][colIdx].SetBlockPiece(BISHOP);
        }
        else if (QUEEN_FIRST_POS == colIdx)
        {
            m_Block[rowIdx][colIdx].SetBlockPiece(QUEEN);
        }
        else if (KING_FIRST_POS == colIdx)
        {
            m_Block[rowIdx][colIdx].SetBlockPiece(KING);
        }
    }
    else if ((BLACK_ROW_2 == rowIdx) || (WHITE_ROW_2 == rowIdx))
    {
        m_Block[rowIdx][colIdx].SetBlockPiece(PAWN);
    }
    else
    {
        m_Block[rowIdx][colIdx].SetBlockPiece(EMPTY);
    }
}

int Chess::GetTextures()
{
    if (!m_Font.loadFromFile(gChessPath + "sansation.ttf"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open Font \n");
        return EXIT_FAILURE;
    }

    if (!m_ChessTexture.loadFromFile(gChessPath + "ChessBoard.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackPawnTexture.loadFromFile(gChessPath + "BlackPawn.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackBishopTexture.loadFromFile(gChessPath + "BlackBishop.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackKnightTexture.loadFromFile(gChessPath + "Blackknight.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackKingTexture.loadFromFile(gChessPath + "BlackKing.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackQueenTexture.loadFromFile(gChessPath + "BlackQueen.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackRookTexture.loadFromFile(gChessPath + "BlackRook.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhitePawnTexture.loadFromFile(gChessPath + "WhitePawn.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteBishopTexture.loadFromFile(gChessPath + "WhiteBishop.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteKnightTexture.loadFromFile(gChessPath + "Whiteknight.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteKingTexture.loadFromFile(gChessPath + "WhiteKing.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteQueenTexture.loadFromFile(gChessPath + "WhiteQueen.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteRookTexture.loadFromFile(gChessPath + "WhiteRook.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WoodenBackGroundTexture.loadFromFile(gChessPath + "WoodenBackGround.jpeg"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_CursorBlockTexture.loadFromFile(gChessPath + "CursorBlock.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_SelectedBlockTexture.loadFromFile(gChessPath + "SelectedBlock.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }



    if (!m_BlackPawnTextureCut.loadFromFile(gChessPath + "BlackPawnCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackBishopTextureCut.loadFromFile(gChessPath + "BlackBishopCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackKnightTextureCut.loadFromFile(gChessPath + "BlackknightCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackKingTextureCut.loadFromFile(gChessPath + "BlackKingCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackQueenTextureCut.loadFromFile(gChessPath + "BlackQueenCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_BlackRookTextureCut.loadFromFile(gChessPath + "BlackRookCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhitePawnTextureCut.loadFromFile(gChessPath + "WhitePawnCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteBishopTextureCut.loadFromFile(gChessPath + "WhiteBishopCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteKnightTextureCut.loadFromFile(gChessPath + "WhiteknightCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteKingTextureCut.loadFromFile(gChessPath + "WhiteKingCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteQueenTextureCut.loadFromFile(gChessPath + "WhiteQueenCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    if (!m_WhiteRookTextureCut.loadFromFile(gChessPath + "WhiteRookCut.png"))
    {
        LogError(BIT_CHESS, "Chess::PlayeGame(), Can Not Open image \n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
