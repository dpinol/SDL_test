/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelSwap.h"
#include "JewelBoard.h"
#include "JewelObject.h"

JewelSwap::JewelSwap(BoardPos const pos1, BoardPos const pos2)
  :m_positions{pos1, pos2},
    m_board(NULL),
    m_validated(false)
{

}
/*
void JewelSwap::kill(BoardPos const pos)
{
 JewelObject &j =  m_board->getJewel(pos);
 j.kill();
}*/

bool JewelSwap::findMatch(int posIndex) const
{
  bool match = false;
  //newJewel will be at posIndex
  JewelObject &newJewel = m_board->getJewel(m_positions[ 1 - posIndex]);
  JewelObject &otherJewel = m_board->getJewel(m_positions[ posIndex]);

  BoardPos const pos = m_positions[posIndex];

  for(int d=0; d < 4; d++)
  {
    BoardPos const &dir = BoardPos::m_directions[d];
    BoardPos cur = pos + dir;
    if(cur == otherJewel.getBoardPos())
      continue;
    short len = 0;
    while (cur.isValid() )
    {
      if (m_board->getJewel(cur).getColor() != newJewel.getColor())
        break;
      len++;
      cur += dir;
    }
    if (len >= MIN_STRIKE_LEN)
    {
      for (short l = len; l > 0; l--)
      {
        m_board->getJewel(cur).kill();
        cur -= dir;
      }
      match = true;
    }
  }
  return match;
}

bool JewelSwap::isValid() const
{
  bool valid = findMatch(0);
  //order important to avoid shortcut
  valid = findMatch(1) || valid;
  m_validated = true;
  return valid;
}

void JewelSwap::setBoard(JewelBoard &board)
{
  m_board = &board;
}

bool JewelSwap::run()
{
  JewelObject *j1 = &m_board->getJewel(m_positions[0]);
  JewelObject *j2 = &m_board->getJewel(m_positions[1]);
  //m_board->_jewels[pos1.m_row][pos1.m_col] = j2;
  //_jewels[pos2.m_row][pos2.m_col] = j1;
  return true;
}

