# Skeleton makefile for the C++ Chess exercise.
# Make sure that you add any new files you create to this makefile.

OBJ_FILES   = $(CHESS_BOARD) $(PIECES)
CHESS_BOARD = ChessMain.o ChessBoard.o ChessBoard_check.o
PIECES      = Pieces/Pieces_base.o Pieces/Pieces_all.o
CXX         = g++
CXXFLAGS    = -Wall -std=c++11 -g -c 
LFLAGS      = -Wall -std=c++11 -g

Chess: $(OBJ_FILES)
	$(CXX) $(LFLAGS) $(OBJ_FILES) -o Chess

Chess%.o: Chess%.cpp ChessBoard.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Pieces/Pieces_%.o: Pieces/Pieces_%.cpp Pieces/Pieces.hpp ChessBoard.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o Pieces/*.o Chess