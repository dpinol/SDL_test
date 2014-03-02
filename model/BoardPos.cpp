/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "BoardPos.h"


BoardPos const BoardPos::m_directions[4] = {{0,1}, {0, -1}, {-1, 0}, {1,0}};

std::ostream& operator<<(std::ostream& os, const BoardPos& obj)
{
  os << "(" << obj.m_col << "," << obj.m_row << ")";
  return os;
}
