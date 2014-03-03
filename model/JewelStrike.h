/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWELSTRIKE_H
#define JEWELSTRIKE_H


#include "BoardPos.h"
#include "Board.h"
#include "Jewel.h"
/**
* A strike is when 3 or more jewels are aligned with same color
*/
class JewelStrike
{
public:
  /**
   * @brief MIN_LEN minimum len to be a strike
   */
  constexpr static short MIN_LEN = 3;

  JewelStrike(Board &board);
  /**
   * @brief findMatch
   * @param newPos
   * @param newColor
   * @param ignorePos in case of a swap, don't check the position color, as for sure it does
   * not match. If invalid, argument is not taken into account
   * @return
   */
  bool findMatch(BoardPos newPos, Jewel::COLOR newColor, BoardPos ignorePos = BoardPos()) const;

private:
  Board &m_board;
};

#endif // JEWELSTRIKE_H
