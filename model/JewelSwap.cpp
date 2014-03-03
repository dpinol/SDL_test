/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelSwap.h"
#include "Board.h"
#include "Jewel.h"
#include "JewelStrike.h"

JewelSwap::JewelSwap(Board &board)
  :m_board(board),
    m_validated(false)

{

}

void JewelSwap::setPositions(BoardPos const pos1, BoardPos const pos2)
{
  m_positions[0] = pos1;
  m_positions[1] = pos2;
  m_validated = false;
}
/*
void JewelSwap::kill(BoardPos const pos)
{
 JewelObject &j =  m_board->getJewel(pos);
 j.kill();
}*/

bool JewelSwap::isValid() const
{
  JewelStrike strike(m_board);
  bool valid = strike.findMatch(m_positions[0], m_board.getJewel(m_positions[1]).getColor());
  //order important to avoid shortcut
  valid = strike.findMatch(m_positions[1], m_board.getJewel(m_positions[0]).getColor()) || valid;
  m_validated = true;
  return valid;
}


bool JewelSwap::run()
{
  if (!isValid())
    return false;
  Jewel j1 = m_board.getJewel(m_positions[0]);
  Jewel &j2 = m_board.getJewel(m_positions[1]);
  m_board.getJewel(m_positions[0]) = j2;
  j2 = j1;
  //m_board->_jewels[pos1.m_row][pos1.m_col] = j2;
  //_jewels[pos2.m_row][pos2.m_col] = j1;
  return true;
}
