/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWEL_H
#define JEWEL_H
#include "BoardPos.h"

class Board;

class Jewel
{
public:
  typedef short COLOR;
  /**
   * @brief Jewel by default it has color NO_COLOR
   */
  Jewel();
  static constexpr short NUM_COLORS = 3;
  static constexpr COLOR NO_COLOR = -1;

  void setColor(COLOR color) { m_color = color;}
  COLOR getColor() const { return m_color;}
  //BoardPos const getBoardPos() const { return m_boardPos;}

private:

  friend class Board;
  COLOR m_color;
//  BoardPos m_boardPos;

};

#endif // JEWEL_H
