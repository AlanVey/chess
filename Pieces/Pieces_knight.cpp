////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_knight.cpp
// Desc: Defines all methods for knight class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

Knight::Knight(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Knight::validMove(const char* from, const char* to, struct game *game)
{
  if(~BasePiece::validMove(from, to, game))
    return false;

  return (rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2);
}

bool Knight::isKnight()
{
  return true;
}

