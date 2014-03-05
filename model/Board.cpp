/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Board.h"
#include "JewelStrike.h"
#include "utils/utils.h"
#include <stdexcept>

Board::Board(BoardCallback &callback)
  :m_callback(callback)
{
  randomize();
}

void Board::randomize()
{
  JewelStrike strike(*this);
  forAllPos([&](BoardPos const &pos)
  {
    Jewel& jewel = getJewel(pos);
    if (pos.m_row == 0)
    {
      //it will reset anyway (without findMatch) when it starts falling
      jewel.setColor(Jewel::NO_COLOR);
      return;
    }
    do
    {
      jewel.setColor(random() % Jewel::NUM_COLORS);
    } while (strike.findMatch(pos, jewel.getColor()));
  });
}
#ifdef NDEBUG
inline static void assertBoardPos(BoardPos const, bool allowFirstRow = false)
{
}
#else
inline static void assertBoardPos(BoardPos const pos, bool allowFirstRow = false)
{
  if (!pos.isValid(allowFirstRow))
    throw std::runtime_error("BoardPos " + dani::toString(pos) + " is not valid");
}
#endif
Jewel& Board::getJewel(BoardPos const pos, bool alsoFirstRow)
{
  assertBoardPos(pos, alsoFirstRow);
  return m_jewels[pos.m_row][pos.m_col];
}

Jewel const& Board::getJewel(BoardPos const pos, bool alsoFirstRow) const
{
  assertBoardPos(pos, alsoFirstRow);
  return m_jewels[pos.m_row][pos.m_col];
}


void Board::kill(BoardPos pos)
{
  m_callback.kill(pos);
}

void Board::update()
{
}
