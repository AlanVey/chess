////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ChessBoard.hpp
// Desc: Header file for the chess board
////////////////////////////////////////////////////////////////////////////////

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define MAX_FILE 8
#define MAX_RANK 8

#include <iostream>
#include <list>

///////////////////////////////////////////////////////////////////////////////
// Class for base piece
///////////////////////////////////////////////////////////////////////////////

class BasePiece
{
  protected:
    int fromFile, fromRank, fileDiff, rankDiff;
    bool white;

    bool hCheck(int toFile, int toRank, struct game *game);
    bool vCheck(int toFile, int toRank, struct game *game);
    bool dCheck(int toFile, int toRank, struct game *game);

  public:
    BasePiece(int file, int rank, bool white);
    void setFileRank(const char* position);
    int getFile();
    int getRank();
    bool isWhite();
    virtual ~BasePiece();
    virtual bool isKing();
    virtual bool isKnight();
    virtual bool validMove(int toFile, int toRank, struct game *game);
};

///////////////////////////////////////////////////////////////////////////////
// Struct for all Cheass Board data
///////////////////////////////////////////////////////////////////////////////

struct game
{
  bool isWhitesMove;
  BasePiece* board[8][8];
  std::list<BasePiece*> whites;
  std::list<BasePiece*> blacks;
};

///////////////////////////////////////////////////////////////////////////////
// Class for ChessBoard
///////////////////////////////////////////////////////////////////////////////

class ChessBoard
{
  bool notInRange(int min, int max, int value);
  void createPiece(BasePiece* piece);
  void capturePiece(int file, int rank);
  bool kingInCheck(BasePiece* king, int toFile, int toRank);

  public:
    struct game game;

    ChessBoard();
    ~ChessBoard();

    void resetBoard();
    void submitMove(const char* fromSquare, const char* toSquare);
    void nextMove();
    BasePiece* isCheck();
    bool isCheckMate();
    void printBoard();
    bool movePieceToRemoveCheck(BasePiece* piece, BasePiece* king);
};

#endif
