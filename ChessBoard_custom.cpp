///////////////////////////////////////////////////////////////////////////////
// Chess Assignment
//
// File: ChessBoard_custom.cpp
// Desc: Provides all the non skeleton file methods for the chess board
///////////////////////////////////////////////////////////////////////////////

#include "ChessBoard.hpp"

bool ChessBoard::isCheck()
{
  //Trace along verticals, horizontals, diagonals until own piece/ end of board/ opponents piece
  //Always check knights to king valid move
  //If opponets piece check if from it to king == validMove ====> Check
  return false;
}

bool ChessBoard::isCheckMate()
{
  if(ChessBoard::isCheck())
  {
    std::list<BasePiece*> opposition;
    game.isWhitesMove ? opposition = game.blacks : opposition = game.whites;

    for(BasePiece* piece : opposition)
    {
      if(piece->isKing())
      {
          //Move king to each possible position
          //Run isCheck() in each possible position
          //Move King back
          //Find piece causing check and see if own piece can move inbetween
      }
    }
  }
  return false;
}

void ChessBoard::nextMove()
{
  game.isWhitesMove = ~game.isWhitesMove;
}
