/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Jewel.h"
#include <utils/utils.h>
#include <iostream>

Jewel::Jewel():
//  m_boardPos(-1, -1),
  m_color(NO_COLOR)
{
}

std::ostream & operator<<(std::ostream & strm, Jewel &j)
{
  Jewel::COLOR const c = j.getColor();
  strm << (c ==Jewel::NO_COLOR ? "n" : dani::toString(c));
  return strm;
}
