GCC = g++
CPP = c++17

CHESS_SRC = src/
CHESS_INC = include/

LOGGER_SRC = Logger/src/
LOGGER_INC = Logger/include/

SFML_GRAPHICS = -lsfml-graphics
SFML_SYSTEM = -lsfml-system
SFML_WINDOW = -lsfml-window

SFML_LIB = $(SFML_GRAPHICS)
SFML_LIB += $(SFML_SYSTEM)
SFML_LIB += $(SFML_WINDOW)

SRC = Main.cpp
SRC+= $(CHESS_SRC)Chess.cpp
SRC+= $(CHESS_SRC)InitChess.cpp
SRC += $(CHESS_SRC)Block.cpp
SRC += $(CHESS_SRC)Print.cpp
SRC += $(CHESS_SRC)Player.cpp

SRC += $(CHESS_SRC)Default.cpp
SRC += $(CHESS_SRC)King.cpp
SRC += $(CHESS_SRC)Queen.cpp
SRC += $(CHESS_SRC)Bishop.cpp
SRC += $(CHESS_SRC)Rook.cpp
SRC += $(CHESS_SRC)Knight.cpp
SRC += $(CHESS_SRC)Pawn.cpp

SRC += $(CHESS_SRC)Move.cpp

SRC += $(LOGGER_SRC)Logger.cpp

INC = -I$(CHESS_INC)
INC += -I$(LOGGER_INC)

OBJ = chess.out

default:
	$(GCC) -g -std=$(CPP) $(SRC) $(SFML_LIB) $(INC) $(SFML_LIB) -o$(OBJ)

clean:
	rm -rf chess.out
	rm -rf chess.out.dSYM
