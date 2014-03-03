/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWELSWAP_H
#define JEWELSWAP_H

#include "Board.h"
#include "BoardPos.h"
#include <vector>
/**
 * @brief The JewelSwap class swaps two adjacent jewels
 * If the game had more types of moves, it could inherit from a JewelMove
 * interface to implement a Command Patter (optionally allowing undo)
 */
class JewelSwap
{
public:

  JewelSwap(Board &board);
  void setPositions(const BoardPos pos1, const BoardPos pos2);
  bool isValid() const;
  /**
   * @brief run will try to perform the move. If not possible (because
   * it does not cause an strike), it will revert to previous position
   * @return whether the swap is possible
   */
  bool run();
private:
  BoardPos m_positions[2];
  Board &m_board;
  mutable bool m_validated;
  mutable bool m_valid;
  /**
   * @brief m_strike has the
   */
  mutable std::vector<BoardPos> m_strike;
};

#endif // JEWELSWAP_H
