////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces.hpp
// Desc: Header file for all Piece classes
////////////////////////////////////////////////////////////////////////////////
#ifndef PIECES_H
#define PIECES_H

#include "../ChessBoard.hpp"

///////////////////////////////////////////////////////////////////////////////
// Classes for all other pieces
///////////////////////////////////////////////////////////////////////////////

class King : public BasePiece
{
  public:
    King(int file, int rank, bool white);
    bool validMove(int toFile, int toRank, struct game *game);  
    bool isKing();
};

class Rook : public BasePiece
{
  public:
    Rook(int file, int rank, bool white);
    bool validMove(int toFile, int toRank, struct game *game);
};

class Bishop : public BasePiece
{
  public:
    Bishop(int file, int rank, bool white);
    bool validMove(int toFile, int toRank, struct game *game);
};

class Queen : public BasePiece
{
  public:
    Queen(int file, int rank, bool white);
    bool validMove(int toFile, int toRank, struct game *game);
};

class Knight : public BasePiece
{
  public:
    Knight(int file, int rank, bool white);
    bool validMove(int toFile, int toRank, struct game *game);
    bool isKnight();
};

class Pawn : public BasePiece
{
  protected:
    bool firstMove;
  public:
    Pawn(int file, int rank, bool white);
    bool validMove(int toFile, int toRank, struct game *game);
};

#endif
