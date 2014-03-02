/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelSwap.h"
#include "JewelBoard.h"
#include "JewelObject.h"

JewelSwap::JewelSwap(JewelBoard::Position const pos1, JewelBoard::Position const pos2)
{
}

bool JewelSwap::areSwappable(Position const pos1, Position const pos2) const
{
}

bool JewelSwap::run()
{
  JewelObject *j1 = &getJewel(pos1);
  JewelObject *j2 = &getJewel(pos2);
  _jewels[pos1.m_row][pos1.m_col] = j2;
  _jewels[pos2.m_row][pos2.m_col] = j1;
  return true;
}

