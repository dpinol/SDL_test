/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef BOARDPOS_H
#define BOARDPOS_H

struct BoardPos
{
  typedef unsigned char ROW;
  typedef unsigned char COL;

  //BoardPos(BoardPos const&);
  BoardPos(COL col, ROW row)
    :m_col(col), m_row(row)
  {
  }
  BoardPos operator+(const BoardPos& v2) const { return BoardPos(m_col + v2.m_col, m_row + v2.m_row); }
  BoardPos& operator+=(const BoardPos& v2) { m_col += v2.m_col; m_row += v2.m_row; return *this;}

  COL m_col;
  ROW m_row;
};

#endif // BOARDPOS_H
