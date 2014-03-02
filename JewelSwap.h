/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWELSWAP_H
#define JEWELSWAP_H

#include "JewelBoard.h"
#include "model/BoardPos.h"
#include <vector>
/**
 * @brief The JewelSwap class swaps two adjacent jewels
 * If the game had more types of moves, it could inherit from a JewelMove
 * interface to implement a Command Patter (optionally allowing undo)
 * A strike is when 3 or more jewels are aligned with same color
 */
class JewelSwap
{
public:
  /**
   * @brief MIN_STRIKE_LEN minimum len to be a strike
   */
  constexpr static short MIN_STRIKE_LEN = 3;

  JewelSwap(const BoardPos pos1, const BoardPos pos2);
  void setBoard(JewelBoard &board);
  bool isValid() const;
  /**
   * @brief run will try to perform the move. If not possible (because
   * it does not cause an strike), it will revert to previous position
   * @return whether the swap is possible
   */
  bool run();
private:
  BoardPos const m_positions[2];
  JewelBoard *m_board;
  mutable bool m_validated;
  bool findMatch(int posIndex) const;
  /**
   * @brief m_strike has the
   */
  mutable std::vector<BoardPos> m_strike;
};

#endif // JEWELSWAP_H
