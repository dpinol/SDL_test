/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWELSWAP_H
#define JEWELSWAP_H

#include "JewelBoard.h"
/**
 * @brief The JewelSwap class swaps two adjacent jewels
 * If the game had more types of moves, it could inherit from a JewelMove
 * interface to implement a Command Patter (optionally allowing undo)
 */
class JewelSwap
{
public:
  JewelSwap(const JewelBoard::Position pos1, const JewelBoard::Position pos2);
  bool isValid() const;
  void run();
};

#endif // JEWELSWAP_H
