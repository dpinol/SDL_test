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

  /**
   * @brief JewelStrike
   * @param board
   * @param callback if set, its kill() will be called for each jewel on detected strikes
   */
  JewelStrike(Board &board, BoardCallback * callback = NULL);

  /**
   * @brief findMatch detects whether in case we move a newColor jewel into newPos, we would
   * be creating any strike
   * @param newPos
   * @param newColor
   * @param ignorePos in case of a swap, don't check the position color, as for sure it does
   * not match. If invalid, argument is not taken into account
   * @return whether any strike is created
   */
  bool findMatch(BoardPos newPos, Jewel::COLOR newColor, BoardPos ignorePos = BoardPos()) const;

private:
  Board& m_board;
  BoardCallback* m_callback;
};

#endif // JEWELSTRIKE_H
