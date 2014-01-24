////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_queen.cpp
// Desc: Defines all methods for queen class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"

Pawn::Pawn(int file, int rank, bool white) : BasePiece(file, rank, white)
{
  this->firstMove = true;
}

bool Pawn::validMove(const char* from, const char* to, struct game *game)
{
  bool moved;
  int validDirection;

  if(~BasePiece::validMove(from, to, game))
    return false;
  
  firstMove ? moved = rankDiff <= 2 : moved = rankDiff == 1; 
  white ? validDirection = 1 : validDirection = -1;

  if(((moved && fileDiff == 0) || (rankDiff == 1 && fileDiff == 1)) && 
       ((rankFinish - rankStart) * validDirection > 0))
  {
    if(fileDiff == rankDiff && game->board[fileFinish][rankFinish] != 0)
    {
      firstMove = false;
      return true;
    }
    else if(fileDiff != rankDiff && game->board[fileFinish][rankFinish] == 0)
    {
      firstMove = false;
      return true;
    }
  }
  return false;
}

