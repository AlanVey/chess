////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ChessBoard.cpp
// Desc: Provides all public methods for the chess board
////////////////////////////////////////////////////////////////////////////////

#include "ChessBoard.hpp"
#include "Pieces/Pieces.hpp"

ChessBoard::ChessBoard()
{
  ChessBoard::resetBoard();
}

ChessBoard::~ChessBoard()
{  
  for(BasePiece* piece : game.blacks) { delete piece; }
  for(BasePiece* piece : game.whites) { delete piece; }

}

void ChessBoard::submitMove(const char* fromSquare, const char* toSquare)
{
  int fromFile = fromSquare[0] - 'A';
  int fromRank = fromSquare[1] - '1';
  int toFile   = toSquare[0] - 'A';
  int toRank   = toSquare[1] - '1';

  if(game.board[fromFile][fromRank]->validMove(fromSquare, toSquare, &game))
  {
    if(game.board[toFile][toRank]->isKing() && ChessBoard::kingInCheck(fromSquare, toSquare))
      return;

    if(game.board[toFile][toRank] != 0)
      ChessBoard::capturePiece(toFile, toRank);

    game.board[fromFile][fromRank]->setFileRank(toSquare);
    game.board[fromFile][fromRank] = 0;

    //TODO: Add functionality to force player to get king out of check
    ChessBoard::isCheck();
    ChessBoard::nextMove();

    if(ChessBoard::isCheckMate())
      ChessBoard::resetBoard();
  }
}    

void ChessBoard::resetBoard()
{
  ChessBoard::~ChessBoard();
  game.blacks.clear();
  game.whites.clear();
  game.isWhitesMove = true;

  for(int file = 0; file < MAX_FILE; file++) 
  { 
    for(int rank = 0; rank < MAX_RANK; rank++)
    {
      game.board[file][rank] = 0;
      if(rank == 1 || rank == 6)
        ChessBoard::createPiece(new Pawn(file, rank, rank == 1));
      else if(rank == 0 || rank == 7)
      {
        if(file == 0 || file == 7)
          ChessBoard::createPiece(new Rook(file, rank, rank == 0));
        if(file == 1 || file == 6)
          ChessBoard::createPiece(new Knight(file, rank, rank == 0));
        if(file == 2 || file == 5)
          ChessBoard::createPiece(new Bishop(file, rank, rank == 0));
        if(file == 3)
          ChessBoard::createPiece(new King(file, rank, rank == 0));
        else
          ChessBoard::createPiece(new Queen(file, rank, rank == 0));
      }
    }
  }
  std::cout << "New Game Started..." << std::endl;
}

void ChessBoard::createPiece(BasePiece* piece)
{
  game.board[piece->getFile()][piece->getRank()] = piece;
  if(piece->isWhite())
    game.whites.push_front(piece);
  else
    game.blacks.push_front(piece);
}

void ChessBoard::capturePiece(int file, int rank)
{
  BasePiece* piece = game.board[file][rank];
  
  if(piece->isWhite()) 
    game.whites.remove(piece);
  else
    game.blacks.remove(piece);

  delete piece;
  game.board[file][rank] = 0;
}

bool ChessBoard::kingInCheck(const char* from, const char* to)
{
  const int fromFile   = from[0] - 'A';
  const int fromRank   = from[1] - '1';
  const int toFile     = to[0]   - 'A';
  const int toRank     = to[1]   - '1';
  BasePiece* king      = game.board[fromFile][fromRank];
  BasePiece* destPiece = game.board[toFile][toRank];

  game.board[fromFile][fromRank] = 0;
  game.board[toFile][toRank]     = king;

  if(ChessBoard::isCheck())
  {  
    game.board[fromFile][fromRank] = king;
    game.board[toFile][toRank]     = destPiece;
    std::cout << "You cannot move your king into check" << std::endl;
    return true;
  }
  return false;
}
