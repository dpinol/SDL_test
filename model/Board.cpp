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

Board::Board()
  :m_callback(NULL)
{
  forAllPos([&](BoardPos const &pos)
  {
    m_jewels[pos.m_row][pos.m_col] = new Jewel;
  }, true);
  randomize();
}

Board::~Board()
{
  forAllPos([&](BoardPos const &pos)
  {
    delete m_jewels[pos.m_row][pos.m_col];
  }, true);
}

void Board::setCallback(BoardCallback *callback)
{
  m_callback = callback;
}
BoardCallback& Board::getCallback()
{
  return *m_callback;
}

const BoardCallback& Board::getCallback() const
{
  return *m_callback;
}
void Board::randomize()
{
  JewelStrike strike(*this);
  forAllPos([&](BoardPos const &pos)
  {
    Jewel& jewel = getJewel(pos, true);
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
  }, true);
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
  return *m_jewels[pos.m_row][pos.m_col];
}

Jewel const& Board::getJewel(BoardPos const pos, bool alsoFirstRow) const
{
  assertBoardPos(pos, alsoFirstRow);
  return *m_jewels[pos.m_row][pos.m_col];
}

void Board::pureSwap(BoardPos pos, BoardPos pos2)
{
  /*getJewel(BoardPos(pos.m_col, pos.m_row + 1)) = jo;
  getJewel(BoardPos(pos.m_col, pos.m_row)).resetFalling();*/
  std::swap( m_jewels[pos.m_row][pos.m_col], m_jewels[pos2.m_row][pos2.m_col]);
}
/*
void Board::kill(BoardPos pos)
{
  m_callback->kill(pos);
  //getJewel(pos).setColor(Jewel::NO_COLOR);
}

bool Board::isAlive(BoardPos pos) const
{
  return m_callback->isAlive(pos);
}
*/
void Board::update()
{
}
