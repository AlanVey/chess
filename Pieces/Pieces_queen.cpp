////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_queen.cpp
// Desc: Defines all methods for queen class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

Queen::Queen(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Queen::validMove(const char* from, const char* to, struct game *game)
{
  if(~BasePiece::validMove(from, to, game))
    return false;

  if(rankDiff == 0)
    return BasePiece::vCheck(game);
  else if(fileDiff == 0)
    return BasePiece::hCheck(game);
  else if(fileDiff == rankDiff)
    return BasePiece::dCheck(game);

  return false;
}
