/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Board.h"
#include "utils/utils.h"

Board::Board(BoardCallback &callback)
  :m_callback(callback)
{
}
#ifdef NDEBUG
inline void assertBoardPos(BoardPos const)
{
}
#else
inline void assertBoardPos(BoardPos const pos)
{
  if (!pos.isValid())
    throw std::runtime_error("BoardPos " + dani::toString(pos) + "is not valid");
}
#endif
Jewel& Board::getJewel(BoardPos const pos)
{
  assertBoardPos(pos);
  return m_jewels[pos.m_row][pos.m_col];
}

Jewel const& Board::getJewel(BoardPos const pos) const
{
  assertBoardPos(pos);
  return m_jewels[pos.m_row][pos.m_col];
}


void Board::kill(BoardPos pos)
{
  m_callback.kill(pos);
}