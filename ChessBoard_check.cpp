///////////////////////////////////////////////////////////////////////////////
// Chess Assignment
//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ChessBoard_custom.cpp
// Desc: Provides all the non skeleton file methods for the chess board
///////////////////////////////////////////////////////////////////////////////

#include "ChessBoard.hpp"

BasePiece* ChessBoard::isCheck()
{ //TODO: possibly more efficient
    //Trace along verticals, horizontals, diagonals until own piece/ end of board/ opponents piece
    //Always check knights to king valid move
    //If opponets piece check if from it to king == validMove ====> Check
  int kingFile;
  int kingRank;
  std::list<BasePiece*> opponent;
  std::list<BasePiece*> player;

  if(game.isWhitesMove)
  { 
    player   = game.whites;
    opponent = game.blacks;
  } 
  else 
  {
    player   = game.blacks;
    opponent = game.whites;
  }

  for(BasePiece* piece : opponent)
  {
    if(piece->isKing())
    {
      kingFile = piece->getFile();
      kingRank = piece->getRank();
    }
  }

  for(BasePiece* piece : player)
  {
    if(!piece->isKing() && piece->validMove(kingFile, kingRank, &game))
      return piece;
  }
  return 0;
}

bool ChessBoard::isCheckMate()
{
  std::list<BasePiece*> player;
  game.isWhitesMove ? player = game.whites : player = game.blacks;

  for(BasePiece* piece : player)
  {
    if(piece->isKing())
    {
      for(int i = -1; i <= 1; i++)
      {
        for(int j = -1; j <= 1; j++)
        {
          int kingFile = piece->getFile() + i;
          int kingRank = piece->getRank() + j;

          if(game.board[kingFile][kingRank]->isWhite() != piece->isWhite() && 
           !(kingFile == 0 && kingRank == 0) && !kingInCheck(piece, kingFile, kingRank))
            return false;
        }
      }
      nextMove();
      BasePiece* pieceCheckingKing = isCheck();
      if(pieceCheckingKing != 0)
      {
        if(movePieceToRemoveCheck(pieceCheckingKing, piece))
          return false;
        std::cout << "CHECKMATE" << std::endl;
      }
      else
        std::cout << "STALEMATE" << std::endl;
      nextMove();
    }
  }
  return true;
}

// Very Last minute rubbish function
bool ChessBoard::movePieceToRemoveCheck(BasePiece* piece, BasePiece* king)
{
  int files[8];
  int ranks[8];

  if(piece->getFile() == king->getFile())
  {
    if(piece->getFile() < king->getFile())
    {
      for(int i = 0; piece->getFile() < king->getFile() - 1; i++)
      {
        files[i] = piece->getFile() + 1 + i;
      }
    }
    else 
    {
      for(int i = 0; piece->getFile() > king->getFile() + 1; i--)
      {
        files[i] = piece->getFile() - 1 + i;
      }
    }
  }
  else if(piece->getRank() == king->getRank())
  {
    if(piece->getRank() < king->getRank())
    {
      for(int i = 0; piece->getRank() < king->getRank() - 1; i++)
      {
        files[i] = piece->getRank() + 1 + i;
      }
    }
    else
    {
      for(int i = 0; piece->getRank() > king->getRank() + 1; i--)
      {
        files[i] = piece->getRank() - 1 + i;
      }
    }
  }
  else { /* TODO: Diagonal cases */ }

  std::list<BasePiece*> player;
  game.isWhitesMove ? player = game.whites : player = game.blacks; 
  for(BasePiece* piece : player)
  {
    for(int i = 0; i < 8; i++)
    {
      if(piece->validMove(files[i], ranks[i], &game))
        return true;
    }
  }

  return false;
}

void ChessBoard::nextMove()
{
  game.isWhitesMove = ~game.isWhitesMove;
}
