////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_all.cpp
// Desc: Defines all methods for all Pieces
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

////////////////////////////////////////////////////////////////////////////////
// Bishop Implementation
////////////////////////////////////////////////////////////////////////////////

Bishop::Bishop(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Bishop::validMove(int toFile, int toRank, struct game *game)
{
  if(!BasePiece::validMove(toFile, toRank, game))
    return false;

  if(fileDiff == rankDiff)
    return BasePiece::dCheck(toFile, toRank, game);

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// King Implementation
////////////////////////////////////////////////////////////////////////////////

King::King(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool King::validMove(int toFile, int toRank, struct game *game)
{
  if(!BasePiece::validMove(toFile, toRank, game))
    return false;

  return fileDiff <= 1 && rankDiff <= 1;
}

bool King::isKing() { return true; }

////////////////////////////////////////////////////////////////////////////////
// Kinght Implementation
////////////////////////////////////////////////////////////////////////////////

Knight::Knight(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Knight::validMove(int toFile, int toRank, struct game *game)
{
  if(!BasePiece::validMove(toFile, toRank, game))
    return false;

  return (rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2);
}

bool Knight::isKnight()
{
  return true;
}

////////////////////////////////////////////////////////////////////////////////
// Pawn Implementation
////////////////////////////////////////////////////////////////////////////////

Pawn::Pawn(int file, int rank, bool white) : BasePiece(file, rank, white)
{
  this->firstMove = true;
}

bool Pawn::validMove(int toFile, int toRank, struct game *game)
{
  bool moved;
  int validDirection;

  if(!BasePiece::validMove(toFile, toRank, game))
    return false;
  
  firstMove ? moved = rankDiff <= 2 : moved = rankDiff == 1; 
  white ? validDirection = 1 : validDirection = -1;

  if(((moved && fileDiff == 0) || (rankDiff == 1 && fileDiff == 1)) && 
       ((toRank - fromRank) * validDirection > 0))
  {
    if(fileDiff == rankDiff && game->board[toFile][toRank] != 0)
    {
      firstMove = false;
      return true;
    }
    else if(fileDiff != rankDiff && game->board[toFile][toRank] == 0)
    {
      firstMove = false;
      return true;
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////
// Queen Implementation
////////////////////////////////////////////////////////////////////////////////

Queen::Queen(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Queen::validMove(int toFile, int toRank, struct game *game)
{
  if(!BasePiece::validMove(toFile, toRank, game))
    return false;

  if(rankDiff == 0)
    return BasePiece::vCheck(toFile, toRank, game);
  else if(fileDiff == 0)
    return BasePiece::hCheck(toFile, toRank, game);
  else if(fileDiff == rankDiff)
    return BasePiece::dCheck(toFile, toRank, game);

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// Rook Implementation
////////////////////////////////////////////////////////////////////////////////

Rook::Rook(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Rook::validMove(int toFile, int toRank, struct game *game)
{
  if(!BasePiece::validMove(toFile, toRank, game))
    return false;
  
  if(rankDiff == 0)
    return BasePiece::vCheck(toFile, toRank, game);
  if(fileDiff == 0)
    return BasePiece::hCheck(toFile, toRank, game);

  return false;
}