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
  static inline bool inRange(int min, int max, int item)
  {
    return item >= min && item <= max;
  }

  protected:
    int file, rank, fileStart, fileFinish, rankStart, rankFinish, fileDiff, rankDiff;
    bool white;

    bool hCheck(struct game *game);
    bool vCheck(struct game *game);
    bool dCheck(struct game *game);

  public:
    BasePiece(int file, int rank, bool white);
    void setFileRank(const char* position);
    int getFile();
    int getRank();
    bool isWhite();
    virtual ~BasePiece();
    virtual bool isKing();
    virtual bool isKnight();
    virtual bool validMove(const char* from, const char* to, struct game *game);
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
  void createPiece(BasePiece* piece);
  void capturePiece(int file, int rank);

  public:
    struct game game;

    ChessBoard();
    ~ChessBoard();

    void resetBoard();
    void submitMove(const char* fromSquare, const char* toSquare);
    void nextMove();
    bool isCheck();
    bool isCheckMate();
};

#endif
