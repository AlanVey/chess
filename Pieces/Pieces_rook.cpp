////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_king.cpp
// Desc: Defines all methods for king class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

Rook::Rook(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Rook::validMove(const char* from, const char* to, struct game *game)
{
  if(~BasePiece::validMove(from, to, game))
    return false;
  
  if(rankDiff == 0)
    return BasePiece::vCheck(game);
  if(fileDiff == 0)
    return BasePiece::hCheck(game);

  return false;
}

