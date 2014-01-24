////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_king.cpp
// Desc: Defines all methods for king class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

King::King(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool King::validMove(const char* from, const char* to, struct game *game)
{
  if(~BasePiece::validMove(from, to, game))
    return false;

  if(fileDiff <= 1 && rankDiff <= 1)
  {
    //TODO: Implement this
    return true;
  }

  return false;
}

bool King::isKing() { return true; }
