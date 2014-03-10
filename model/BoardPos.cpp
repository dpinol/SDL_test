/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "BoardPos.h"
#include <math.h>


BoardPos const BoardPos::m_directions[4] = {{0,1}, {0, -1}, {-1, 0}, {1,0}};

float BoardPos::length() const
{
  return sqrt(m_col * m_col + m_row * m_row);
}

std::ostream& operator<<(std::ostream& os, const BoardPos& obj)
{
  os << "(" << obj.m_col << "," << obj.m_row << ")";
  return os;
}
