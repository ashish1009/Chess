#include "Chess.h"

Chess::Chess()
    : m_Turn(BLACK), m_bGameOver(false), m_bSourceValidity(false), m_bDestinationValidity(false), m_bIsSourceSelected(false)
{
    LogDebug(BIT_CHESS, "Chess::Chess(), Chess Constructor called ... \n");
    InitChess();
}

Chess::~Chess()
{
    LogDebug(BIT_CHESS, "Chess::~Chess(), Chess Destructor Called ... \n");
}

void Chess::GetPlayerInfo()
{
    std::string name;
    std::cout << "Enter the Name of Player with Black Piece : ";
    std::cin >> name;

    m_Player[BLACK].SetPlayerName(name);
    m_Player[BLACK].SetPlayerColor(BLACK);

    std::cout << "Enter the Name of Player with White Piece : ";
    std::cin >> name;

    m_Player[WHITE].SetPlayerName(name);
    m_Player[WHITE].SetPlayerColor(WHITE);
}

unsigned short Chess::GetPlayerIdx() const
{
    return (m_Turn == m_Player[PLAYER_1].GetPlayerColor()) ? (PLAYER_1) : (PLAYER_2);
}

unsigned short Chess::GetOppPlayerIdx() const
{
    return (m_Turn == m_Player[PLAYER_1].GetPlayerColor()) ? (PLAYER_2) : (PLAYER_1);
}

void Chess::ResetSrcBlock(const unsigned short X, const unsigned short Y)
{
    m_Block[X][Y].ResetBlock();
}

void Chess::SetDstBlock(const unsigned short X, const unsigned short Y, const Block &block)
{
    m_Block[X][Y].SetBlock(block.GetBlockColor(), block.GetBlockPiece());
}

void Chess::ToggleTurn()
{
    m_Turn = ((NONE == m_Turn) || (WHITE == m_Turn)) ? BLACK : WHITE;
}

bool Chess::IsSourceValid(const unsigned short X, const unsigned short Y)
{
    const unsigned short playerIdx = this->GetPlayerIdx();

    m_bSourceValidity = false;
    if (m_Player[playerIdx].GetPlayerColor() == m_Block[X][Y].GetBlockColor())
    {
        m_bSourceValidity = true;
        m_Player[GetPlayerIdx()].m_Source.X = X;
        m_Player[GetPlayerIdx()].m_Source.Y = Y;

        m_Player[playerIdx].SetSourcePiece(m_Block[X][Y].GetBlockPiece());
    }
    return m_bSourceValidity;
}

bool Chess::IsDestinationValid(const unsigned short X, const unsigned short Y, bool (Chess::*movePieceFnPtr)(unsigned short, unsigned short))
{
    const unsigned short playerIdx = GetPlayerIdx();

    m_bDestinationValidity = false;
    if (m_Player[playerIdx].GetPlayerColor() == m_Block[X][Y].GetBlockColor())
    {
        m_bDestinationValidity = false;
    }
    else
    {
        m_bDestinationValidity = (this->*movePieceFnPtr)(X, Y);
    }
    return m_bDestinationValidity;
}

int Chess::PlayGame()
{
    // GetPlayerInfo();
    m_Player[BLACK].SetPlayerColor(BLACK);
    m_Player[WHITE].SetPlayerColor(WHITE);

    sf::Clock clock;
    sf::RenderWindow ChessWindow(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "CHESS");

    if (EXIT_FAILURE == GetTextures())
    {
        return EXIT_FAILURE;
    }

    sf::Sprite ChessSprite(m_ChessTexture);

    sf::Sprite BlackPawnSprite(m_BlackPawnTexture);
    sf::Sprite BlackRookSprite(m_BlackRookTexture);
    sf::Sprite BlackBishopSprite(m_BlackBishopTexture);
    sf::Sprite BlackKnightSprite(m_BlackKnightTexture);
    sf::Sprite BlackQueenSprite(m_BlackQueenTexture);
    sf::Sprite BlackKingSprite(m_BlackKingTexture);

    sf::Sprite WhitePawnSprite(m_WhitePawnTexture);
    sf::Sprite WhiteRookSprite(m_WhiteRookTexture);
    sf::Sprite WhiteBishopSprite(m_WhiteBishopTexture);
    sf::Sprite WhiteKnightSprite(m_WhiteKnightTexture);
    sf::Sprite WhiteQueenSprite(m_WhiteQueenTexture);
    sf::Sprite WhiteKingSprite(m_WhiteKingTexture);

    sf::Sprite BlackPawnSpriteCut(m_BlackPawnTextureCut);
    sf::Sprite BlackRookSpriteCut(m_BlackRookTextureCut);
    sf::Sprite BlackBishopSpriteCut(m_BlackBishopTextureCut);
    sf::Sprite BlackKnightSpriteCut(m_BlackKnightTextureCut);
    sf::Sprite BlackQueenSpriteCut(m_BlackQueenTextureCut);
    sf::Sprite BlackKingSpriteCut(m_BlackKingTextureCut);

    sf::Sprite WhitePawnSpriteCut(m_WhitePawnTextureCut);
    sf::Sprite WhiteRookSpriteCut(m_WhiteRookTextureCut);
    sf::Sprite WhiteBishopSpriteCut(m_WhiteBishopTextureCut);
    sf::Sprite WhiteKnightSpriteCut(m_WhiteKnightTextureCut);
    sf::Sprite WhiteQueenSpriteCut(m_WhiteQueenTextureCut);
    sf::Sprite WhiteKingSpriteCut(m_WhiteKingTextureCut);

    sf::Sprite WoodenBackGroundSprite(m_WoodenBackGroundTexture);

    sf::Sprite CursorBlockSprite(m_CursorBlockTexture);
    sf::Sprite SelectedBlockSprite(m_SelectedBlockTexture);

    sf::Text player1Name;
    sf::Text player2Name;
    sf::Text turnPrint;
    sf::Text printWinner;

    player1Name.setFont(m_Font);
    player1Name.setString("PLAYER 1 (BLACK PIECE) : " + m_Player[BLACK].GetPlayerName());
    player1Name.setCharacterSize(FONT_SIZE);
    player1Name.setPosition(CHESS_SIZE, BLACK_OFFSET);
    player1Name.setFillColor(sf::Color::Black);
    player1Name.setStyle(sf::Text::Bold);

    player2Name.setFont(m_Font);
    player2Name.setString("PLAYER 2 (WHITE PIECE) : " + m_Player[WHITE].GetPlayerName());
    player2Name.setCharacterSize(FONT_SIZE);
    player2Name.setPosition(CHESS_SIZE, (BLOCK_SIZE * CHESS_ROW) - WHITE_OFFSET);
    player2Name.setFillColor(sf::Color::White);
    player2Name.setStyle(sf::Text::Bold);

    turnPrint.setFont(m_Font);
    turnPrint.setCharacterSize(FONT_SIZE);
    turnPrint.setPosition(CHESS_SIZE, (BLOCK_SIZE * CHESS_ROW / 2));
    turnPrint.setStyle(sf::Text::Bold);

    printWinner.setFont(m_Font);
    printWinner.setCharacterSize(FONT_SIZE);
    printWinner.setPosition(CHESS_SIZE, (BLOCK_SIZE * CHESS_ROW / 2));
    printWinner.setStyle(sf::Text::Bold);

    while (ChessWindow.isOpen())
    {
        turnPrint.setString("TURN : " + m_Player[m_Turn].GetPlayerName());
        (BLACK == m_Turn) ? turnPrint.setFillColor(sf::Color::Black) : turnPrint.setFillColor(sf::Color::White);

        if (m_bGameOver)
        {
            printWinner.setString("Winner is " + m_Player[GetOppPlayerIdx()].GetPlayerName() + " \n Press N For New Game ... ");
            (BLACK == m_Player[GetOppPlayerIdx()].GetPlayerColor()) ? printWinner.setFillColor(sf::Color::Black) : printWinner.setFillColor(sf::Color::White);
        }

        sf::Event event;
        ChessWindow.clear();
        WoodenBackGroundSprite.setPosition(CHESS_SIZE, 0);
        ChessWindow.draw(WoodenBackGroundSprite);
        ChessWindow.draw(ChessSprite);

        while (ChessWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                ChessWindow.close();
                break;

            case sf::Event::MouseMoved:
                if ((!m_bGameOver) && ((event.mouseMove.x < CHESS_SIZE) && (event.mouseMove.x < CHESS_SIZE)))
                {
                    CursorBlockSprite.setPosition(((event.mouseMove.x / BLOCK_SIZE) * BLOCK_SIZE) % CHESS_SIZE, ((event.mouseMove.y / BLOCK_SIZE) * BLOCK_SIZE) % CHESS_SIZE);
                }
                LogInfo(BIT_CHESS, " Chess::PlayGame(), Cursor at X : %d, Y : %d \n", event.mouseMove.x, event.mouseMove.y);

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if ((!m_bGameOver) && ((event.mouseButton.x < CHESS_SIZE) && (event.mouseButton.x < CHESS_SIZE)))
                    {
                        const unsigned int X = event.mouseButton.y / BLOCK_SIZE;
                        const unsigned int Y = event.mouseButton.x / BLOCK_SIZE;

                        if (m_bIsSourceSelected)
                        {
                            const Position_s src = m_Player[GetPlayerIdx()].GetPlayerSource();
                            m_bIsSourceSelected = false;

                            if (IsDestinationValid(X, Y, m_MovePieceFnPtr[m_Block[src.X][src.Y].GetBlockPiece()]))
                            {
                                m_Player[GetPlayerIdx()].SetSourcePiece(EMPTY);
                                ToggleTurn();
                            }
                        }
                        else if (IsSourceValid((event.mouseButton.y / BLOCK_SIZE), (event.mouseButton.x / BLOCK_SIZE)))
                        {
                            m_bIsSourceSelected = true;
                            SelectedBlockSprite.setPosition(((event.mouseButton.x / BLOCK_SIZE) * BLOCK_SIZE) % CHESS_SIZE, ((event.mouseButton.y / BLOCK_SIZE) * BLOCK_SIZE) % CHESS_SIZE);
                        }

                        else
                        {
                            LogWarning(BIT_CHESS, "Chess::PlayGame(), Invalid Block Selected \n");
                        }
                    }
                    LogInfo(BIT_CHESS, "Chess::PlayGame(), Left Clicked at X : %d, Y : %d \n", (event.mouseButton.x / BLOCK_SIZE), (event.mouseButton.y) / BLOCK_SIZE);
                }

            case sf::Event::TextEntered:
                if (m_bGameOver)
                {
                    if (((event.text.unicode == 'n') || (event.text.unicode == 'N')))
                    {
                        ResetGame();
                    }
                }

            default:
                break;
            }
        }

        if (m_bIsSourceSelected)
        {
            ChessWindow.draw(SelectedBlockSprite);
        }
        ChessWindow.draw(CursorBlockSprite);
        ChessWindow.draw(player1Name);
        ChessWindow.draw(player2Name);

        if (!m_bGameOver)
        {
            ChessWindow.draw(turnPrint);
        }
        else
        {
            ChessWindow.draw(printWinner);
        }

        for (unsigned short rowIdx = 0; rowIdx < CHESS_ROW; rowIdx++)
        {
            for (unsigned short colIdx = 0; colIdx < CHESS_COL; colIdx++)
            {
                switch (m_Block[rowIdx][colIdx].GetBlockPiece())
                {
                case PAWN:
                    if (BLACK == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        BlackPawnSprite.setPosition(PAWN_POS + (colIdx * BLOCK_SIZE), PAWN_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(BlackPawnSprite);
                    }
                    else if (WHITE == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        WhitePawnSprite.setPosition(PAWN_POS + (colIdx * BLOCK_SIZE), PAWN_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(WhitePawnSprite);
                    }
                    else
                    {
                        LogError(BIT_CHESS, "Chess::PlayGame(), Selected(%d, %d) Block Color is not Valid \n", rowIdx, colIdx);
                    }
                    break;

                case KNIGHT:
                    if (BLACK == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        BlackKnightSprite.setPosition(BLACK_KNIGHT_POS + (colIdx * BLOCK_SIZE), BLACK_KNIGHT_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(BlackKnightSprite);
                    }
                    else if (WHITE == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        WhiteKnightSprite.setPosition(BLACK_KNIGHT_POS + (colIdx * BLOCK_SIZE), WHITE_KNIGHT_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(WhiteKnightSprite);
                    }
                    else
                    {
                        LogError(BIT_CHESS, "Chess::PlayGame(), Selected(%d, %d) Block Color is not Valid \n", rowIdx, colIdx);
                    }
                    break;

                case BISHOP:
                    if (BLACK == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        BlackBishopSprite.setPosition(BLACK_BISHOP_POS + (colIdx * BLOCK_SIZE), BLACK_BISHOP_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(BlackBishopSprite);
                    }
                    else if (WHITE == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        WhiteBishopSprite.setPosition(WHITE_BISHOP_POS + (colIdx * BLOCK_SIZE), WHITE_BISHOP_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(WhiteBishopSprite);
                    }
                    else
                    {
                        LogError(BIT_CHESS, "Chess::PlayGame(), Selected(%d, %d) Block Color is not Valid \n", rowIdx, colIdx);
                    }
                    break;

                case ROOK:
                    if (BLACK == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        BlackRookSprite.setPosition(BLACK_ROOK_POS + (colIdx * BLOCK_SIZE), BLACK_ROOK_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(BlackRookSprite);
                    }
                    else if (WHITE == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        WhiteRookSprite.setPosition(WHITE_ROOK_POS + (colIdx * BLOCK_SIZE), WHITE_ROOK_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(WhiteRookSprite);
                    }
                    else
                    {
                        LogError(BIT_CHESS, "Chess::PlayGame(), Selected(%d, %d) Block Color is not Valid \n", rowIdx, colIdx);
                    }
                    break;

                case QUEEN:
                    if (BLACK == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        BlackQueenSprite.setPosition(BLACK_QUEEN_POS + (colIdx * BLOCK_SIZE), BLACK_QUEEN_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(BlackQueenSprite);
                    }
                    else if (WHITE == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        WhiteQueenSprite.setPosition(WHITE_QUEEN_POS + (colIdx * BLOCK_SIZE), WHITE_QUEEN_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(WhiteQueenSprite);
                    }
                    else
                    {
                        LogError(BIT_CHESS, "Chess::PlayGame(), Selected(%d, %d) Block Color is not Valid \n", rowIdx, colIdx);
                    }
                    break;

                case KING:
                    if (BLACK == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        BlackKingSprite.setPosition(BLACK_KING_POS + (colIdx * BLOCK_SIZE), BLACK_KING_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(BlackKingSprite);
                    }
                    else if (WHITE == m_Block[rowIdx][colIdx].GetBlockColor())
                    {
                        WhiteKingSprite.setPosition(WHITE_KING_POS + (colIdx * BLOCK_SIZE), WHITE_KING_POS + (BLOCK_SIZE * rowIdx));
                        ChessWindow.draw(WhiteKingSprite);
                    }
                    else
                    {
                        LogError(BIT_CHESS, "Chess::PlayGame(), Selected(%d, %d) Block Color is not Valid \n", rowIdx, colIdx);
                    }
                    break;

                default:
                    break;
                }
            }
        }

        for (unsigned short idx = 0; idx < m_Player[BLACK].m_NumCutPiece; idx++)
        {
            unsigned const yOffset = (idx < ((Player::MAX_PIECES) >> 1)) ? BLACK_CUT_Y_OFFSET_1 : BLACK_CUT_Y_OFFSET_2;
            static unsigned short xOffset = idx % 4;

            switch (m_Player[BLACK].m_CutPieces[idx])
            {
            case PAWN:
                WhitePawnSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(WhitePawnSpriteCut);
                break;

            case KNIGHT:
                WhiteKnightSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(WhiteKnightSpriteCut);
                break;

            case BISHOP:
                WhiteBishopSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(WhiteBishopSpriteCut);
                break;

            case ROOK:
                WhiteRookSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(WhiteRookSpriteCut);
                break;

            case QUEEN:
                WhiteQueenSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(WhiteQueenSpriteCut);
                break;

            case KING:
                WhiteKingSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(WhiteKingSpriteCut);
                break;

            default:
                break;
            }
        }

        for (unsigned short idx = 0; idx < m_Player[WHITE].m_NumCutPiece; idx++)
        {
            unsigned const yOffset = (idx < ((Player::MAX_PIECES) >> 1)) ? WHITE_CUT_Y_OFFSET_1 : WHITE_CUT_Y_OFFSET_2;
            static unsigned short xOffset = idx % 4;

            switch (m_Player[WHITE].m_CutPieces[idx])
            {
            case PAWN:
                BlackPawnSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(BlackPawnSpriteCut);
                break;

            case KNIGHT:
                BlackKnightSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(BlackKnightSpriteCut);
                break;

            case BISHOP:
                BlackBishopSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(BlackBishopSpriteCut);
                break;

            case ROOK:
                BlackRookSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(BlackRookSpriteCut);
                break;

            case QUEEN:
                BlackQueenSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(BlackQueenSpriteCut);
                break;

            case KING:
                BlackKingSpriteCut.setPosition(CUT_X_OFFSET + ((BLOCK_SIZE >> 1) * idx), yOffset);
                ChessWindow.draw(BlackKingSpriteCut);
                break;

            default:
                break;
            }
        }

        ChessWindow.display();
    }

    sf::Time elapsed = clock.getElapsedTime();
    LogInfo(BIT_CHESS, "Chess::PlayGame(), Time lapsed in Game is : %d \n", elapsed.asSeconds());
    return EXIT_SUCCESS;
}

void Chess::ResetGame()
{
    m_bGameOver = false;
    m_bSourceValidity = false;
    m_bDestinationValidity = false;
    m_bIsSourceSelected = false;

    for (unsigned short playerIdx = 0; playerIdx < MAX_PLAYER; playerIdx++)
    {
        m_Player[playerIdx].Reset();
    }

    InitChess();
}
