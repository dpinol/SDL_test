/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelStrike.h"
#include "Jewel.h"

JewelStrike::JewelStrike(Board &board)
  :m_board(board)
{
}


bool JewelStrike::findMatch(BoardPos newPos, Jewel::COLOR newColor) const
{
  bool match = false;
  //newJewel will be at posIndex
  //Jewel &newJewel = m_board.getJewel(m_positions[ 1 - posIndex]);
  //Jewel &otherJewel = m_board.getJewel(m_positions[ posIndex]);

//  BoardPos const pos = m_positions[posIndex];

  for(int d=0; d < 4; d++)
  {
    BoardPos const &dir = BoardPos::m_directions[d];
    BoardPos cur = newPos + dir;
    //if(cur == otherJewel.getBoardPos())
    //  continue;
    short len = 1;
    while (cur.isValid() )
    {
      if (m_board.getJewel(cur).getColor() != newColor)
        break;
      len++;
      cur += dir;
    }
    if (len >= MIN_LEN)
    {
      for (short l = len; l > 0; l--)
      {
        m_board.kill(cur);
        cur -= dir;
      }
      match = true;
    }
  }
  return match;
}
