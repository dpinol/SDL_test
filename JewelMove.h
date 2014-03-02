/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWELMOVE_H
#define JEWELMOVE_H

struct JewelMove
{
  typedef unsigned char POSITIONS;
  JewelMove(POSITIONS targetX, POSITIONS targetY)
    :m_targetX(targetX),
      m_targetY(targetY)
  {
  }

  POSITIONS m_targetX;
  POSITIONS m_targetY;
};

#endif // JEWELMOVE_H
