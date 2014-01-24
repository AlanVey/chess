////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_bishop.cpp
// Desc: Defines all methods for bishop class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

Bishop::Bishop(int file, int rank, bool white) : BasePiece(file, rank, white) {}

bool Bishop::validMove(const char* from, const char* to, struct game *game)
{
  if(~BasePiece::validMove(from, to, game))
    return false;

  if(fileDiff == rankDiff)
    return BasePiece::dCheck(game);

  return false;
}
