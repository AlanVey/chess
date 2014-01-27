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
  bool notOnBoard = notInRange(0, 7, fromFile) || notInRange(0, 7, toFile) ||
                    notInRange(0, 7, fromRank) || notInRange(0, 7, toRank);

  std::cout << "Your Move: " << fromSquare << toSquare << std::endl;

  if(notOnBoard)
    std::cout << "Specified position is not on the board" << std::endl;
  else if(game.board[fromFile][fromRank] == 0)
    std::cout << "You tried to move a non existant piece" << std::endl;
  else if(game.board[fromFile][fromRank]->
          validMove(toFile, toRank, &game))
  {
    if(game.board[toFile][toRank]->isKing() && 
       ChessBoard::kingInCheck(game.board[toFile][toRank], toFile, toRank))
    {
      std::cout << "You cannot move your king into check" << std::endl;
      return;
    }

    if(game.board[toFile][toRank] != 0)
      ChessBoard::capturePiece(toFile, toRank);

    game.board[fromFile][fromRank]->setFileRank(toSquare);
    game.board[fromFile][fromRank] = 0;

    //TODO: Add functionality to force player to get king out of check
    ChessBoard::isCheck();
    ChessBoard::nextMove();

    //TODO; double check auto reset if checkmate
    //Maybe make all input output game over when in this state
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

bool ChessBoard::kingInCheck(BasePiece* king, int toFile, int toRank)
{
  bool inCheck                                 = false;
  BasePiece* destPiece                         = game.board[toFile][toRank];
  game.board[king->getFile()][king->getRank()] = 0;
  game.board[toFile][toRank]                   = king;
  inCheck                                      = ChessBoard::isCheck() != 0;
  game.board[king->getFile()][king->getRank()] = king;
  game.board[toFile][toRank]                   = destPiece;
  return inCheck;
}

bool ChessBoard::notInRange(int min, int max, int value)
{
  return value > max || value < min;
}

void ChessBoard::printBoard()
{
  std::cout << "Whites turn = " << game.isWhitesMove << std::endl;
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(game.board[i][j] != 0)
        std::cout << "1";
      else
        std::cout << "0";
    }
    std::cout << std::endl;
  }
}
