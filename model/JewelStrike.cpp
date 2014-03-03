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


bool JewelStrike::findMatch(BoardPos newPos, Jewel::COLOR newColor, BoardPos ignorePos) const
{
  bool match = false;
  //newJewel will be at posIndex
  //Jewel &newJewel = m_board.getJewel(m_positions[ 1 - posIndex]);
  //Jewel &otherJewel = m_board.getJewel(m_positions[ posIndex]);

  //  BoardPos const pos = m_positions[posIndex];

  BoardPos directions[] = {{0,1}, {1,0}};
  for(int d=0; d < 2; d++)
  {
    BoardPos dir = directions[d];
    //length on each sense
    short len[2] = {1, 0};
    BoardPos cur;
    //first count on one sense, then on the other
    for(int sense = 0; sense  < 2; sense++)
    {
      cur = newPos + dir;
      while (cur.isValid() )
      {
        if (ignorePos.isValid() && ignorePos == cur)
          break;
        if (m_board.getJewel(cur).getColor() != newColor)
          break;
        len[sense]++;
        cur += dir;
      }
      dir = - dir;
    }
    if (len[0] + len[1] >= MIN_LEN)
    {
      for (short l = -len[1]; l < len[0]; l++)
      {
        m_board.kill(cur);
        cur += directions[d];
      }
      match = true;
    }
  }
  return match;
}
