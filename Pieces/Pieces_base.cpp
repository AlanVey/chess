////////////////////////////////////////////////////////////////////////////////
// Chess Assignment
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: Pieces_base.cpp
// Desc: Defines methods for Pieces Base Class
////////////////////////////////////////////////////////////////////////////////

#include "Pieces.hpp"
#include <stdlib.h>

BasePiece::~BasePiece() {}

BasePiece::BasePiece(int file, int rank, bool white)
{
  this->white = white;
  this->fromFile = file;
  this->fromRank = rank;
}

bool BasePiece::validMove(int toFile, int toRank, struct game *game)
{
  fileDiff   = abs(fromFile - toFile);
  rankDiff   = abs(fromRank - toRank);

  if(game->isWhitesMove && ~game->board[fromFile][fromRank]->white)
  {
    std::cout << "You tried to move an opponents piece" << std::endl;
    return false;
  }
  else if(fileDiff == 0 && rankDiff == 0)
  {
    std::cout << "You tried to move a piece to its current location" << std::endl;
    return false;
  }
  else if(game->board[fromFile][fromRank]->isWhite() != 
          game->board[toFile][toRank]->isWhite())
  {
    std::cout << "You tried to attack your own piece" << std::endl;
    return false;
  }
  return true;
}

bool BasePiece::hCheck(int toFile, int toRank, struct game *game)
{
  int current = fromFile - 1;
  int sign = -1;

  if(fromFile < toFile)
  {
    current = fromFile + 1;
    sign = 1;
  }

  while((sign * current) < (sign * toFile))
  {
    if(game->board[current][fromRank] != 0)
      return false; 
    current += sign;
  }
  return true;
}

bool BasePiece::vCheck(int toFile, int toRank, struct game *game)
{
  int current = fromRank - 1;
  int sign = -1;

  if(fromRank < toRank)
  {
    current = fromRank + 1;
    sign = 1;
  }

  while((sign * current) < (sign * toRank))
  {
    if(game->board[fromFile][current] != 0)
      return false; 
    current += sign;
  }
  return true;
}

// TODO: Double check this method works
bool BasePiece::dCheck(int toFile, int toRank, struct game *game)
{
  int currentH = fromFile - 1;
  int currentV = fromRank - 1;
  int signH = -1;
  int signV = -1;

  if(fromRank < toRank && fromFile < toFile)
  {
    currentH = fromFile + 1;
    currentV = fromRank + 1;
    signH = 1;
    signV = 1;
  }
  else if (fromRank < toRank && fromFile > toFile)
  {
    currentH = fromFile + 1;
    currentV = fromRank - 1;
    signH = 1;
    signV = -1;
  }
  else if (fromRank > toRank && fromFile < toFile)
  {
    currentH = fromFile - 1;
    currentV = fromRank + 1;
    signH = -1;
    signV = 1;
  }

  while((signH * currentH) < (signH * toRank))
  {
    if(game->board[currentH][currentV] != 0)
      return false; 
    currentH += signH;
    currentV += signV;
  }
  return true;
}

void BasePiece::setFileRank(const char* position)
{
  fromFile = position[0] - 'A';
  fromRank = position[1] - '1';
}

int BasePiece::getFile() { return fromFile; }

int BasePiece::getRank() { return fromRank; }

bool BasePiece::isWhite() { return white; }

bool BasePiece::isKing() { return false; }

bool BasePiece::isKnight() { return false; }
