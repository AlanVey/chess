# Skeleton makefile for the C++ Chess exercise.
# Make sure that you add any new files you create to this makefile.

OBJ_FILES = ChessMain.o ChessBoard.o ChessBoard_custom.o $(PIECES)
PIECES = Pieces/Pieces_base.o Pieces/Pieces_bishop.o Pieces/Pieces_pawn.o \
         Pieces/Pieces_king.o Pieces/Pieces_knight.o \
         Pieces/Pieces_queen.o Pieces/Pieces_rook.o
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g -c 
LFLAGS = -Wall -std=c++11 -g

Chess: $(OBJS)
	$(CXX) $(LFLAGS) $(OBJ_FILES) -o Chess

ChessMain.o: ChessBoard.hpp ChessMain.cpp
	$(CXX) $(CXXFLAGS) ChessMain.cpp -o ChessMain.o

ChessBoard%.o: ChessBoard%.cpp ChessBoard.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Pieces/Pieces_%.o: Pieces/Pieces_%.cpp Pieces/Pieces.hpp ChessBoard.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o Pieces/*.o Chess