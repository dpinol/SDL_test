/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 02/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef BOARDPOS_H
#define BOARDPOS_H

#include <ostream>

/**
 * @brief The BoardPos struct
 *  ROW 0 is for the falling jewels when below dies
 */
struct BoardPos
{
  constexpr static short SIZE = 8;
  /** unsigned are evil*/
  typedef short COL;
  typedef short ROW;

  //BoardPos(BoardPos const&);
  /**
   * @brief BoardPos use (x,y) because more typical than C's row-major order
   * @param col
   * @param row
   */
  inline BoardPos(COL col, ROW row)
    :m_col(col), m_row(row)
  {
  }
  inline BoardPos operator+(const BoardPos& v2) const { return BoardPos(m_col + v2.m_col, m_row + v2.m_row); }
  inline BoardPos& operator+=(const BoardPos& v2) { m_col += v2.m_col; m_row += v2.m_row; return *this;}
  inline BoardPos operator-(const BoardPos& v2) const { return BoardPos(m_col - v2.m_col, m_row - v2.m_row); }
  inline BoardPos& operator-=(const BoardPos& v2) { m_col -= v2.m_col; m_row -= v2.m_row; return *this;}
  inline bool operator==(const BoardPos& v2) { return m_col == v2.m_col && m_row == v2.m_row;}

  inline bool isValid() const
  {
    return m_col >= 0 && m_col < SIZE
        && m_row >= 0 && m_row <= SIZE;
  }

  COL m_col;
  ROW m_row;
  static const BoardPos m_directions[4];
};
std::ostream& operator<<(std::ostream& os, const BoardPos& obj);

#endif // BOARDPOS_H
