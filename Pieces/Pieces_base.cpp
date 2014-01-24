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
  this->file = file;
  this->rank = rank;
}

bool BasePiece::validMove(const char* from, const char* to, struct game *game)
{
  fileStart  = from[0] - 'A';
  fileFinish = from[0] - 'A';
  rankStart  = from[1] - '1';
  rankFinish = from[1] - '1';
  fileDiff   = abs(fileStart - fileFinish);
  rankDiff   = abs(rankStart - rankFinish);

  if(inRange(0, 7, fileStart) && inRange(0, 7, fileFinish) &&
     inRange(0, 7, rankStart) && inRange(0, 7, rankStart))
  {
    std::cout << "Specified position is not on the board" << std::endl;
    return false;
  }
  else if(game->board[fileStart][rankStart] != 0)
  {
    std::cout << "You tried to move a non existant piece" << std::endl;
    return false;
  }
  else if(game->isWhitesMove && ~game->board[fileStart][rankStart]->white)
  {
    std::cout << "You tried to move an opponents piece" << std::endl;
    return false;
  }
  else if(fileDiff == 0 && rankDiff == 0)
  {
    std::cout << "You tried to move a piece to its current location" << std::endl;
    return false;
  }
  else if(game->board[fileStart][rankStart]->isWhite() != 
          game->board[fileFinish][rankFinish]->isWhite())
  {
    std::cout << "You tried to attack your own piece" << std::endl;
    return false;
  }
  return true;
}

bool BasePiece::hCheck(struct game *game)
{
  int current = fileStart - 1;
  int sign = -1;

  if(fileStart < fileFinish)
  {
    current = fileStart + 1;
    sign = 1;
  }

  while((sign * current) < (sign * fileFinish))
  {
    if(game->board[current][rankStart] != 0)
      return false; 
    current += sign;
  }
  return true;
}

bool BasePiece::vCheck(struct game *game)
{
  int current = rankStart - 1;
  int sign = -1;

  if(rankStart < rankFinish)
  {
    current = rankStart + 1;
    sign = 1;
  }

  while((sign * current) < (sign * rankFinish))
  {
    if(game->board[fileStart][current] != 0)
      return false; 
    current += sign;
  }
  return true;
}

// TODO: Double check this method works
bool BasePiece::dCheck(struct game *game)
{
  int currentH = fileStart - 1;
  int currentV = rankStart - 1;
  int signH = -1;
  int signV = -1;

  if(rankStart < rankFinish && fileStart < fileFinish)
  {
    currentH = fileStart + 1;
    currentV = rankStart + 1;
    signH = 1;
    signV = 1;
  }
  else if (rankStart < rankFinish && fileStart > fileFinish)
  {
    currentH = fileStart + 1;
    currentV = rankStart - 1;
    signH = 1;
    signV = -1;
  }
  else if (rankStart > rankFinish && fileStart < fileFinish)
  {
    currentH = fileStart - 1;
    currentV = rankStart + 1;
    signH = -1;
    signV = 1;
  }

  while((signH * currentH) < (signH * rankFinish))
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
  file = position[0] - 'A';
  rank = position[1] - '1';
}

int BasePiece::getFile() { return file; }

int BasePiece::getRank() { return rank; }

bool BasePiece::isWhite() { return white; }

bool BasePiece::isKing() { return false; }

bool BasePiece::isKnight() { return false; }
