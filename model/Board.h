/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include "BoardPos.h"
#include "Jewel.h"

struct BoardCallback
{
  virtual void kill(BoardPos pos) = 0;
};

class Board : public BoardCallback
{
public:
  /**
   * @brief Board
   * @param callback
   */
  Board(BoardCallback &callback);

  template<class F>
  inline void forAllPos(F const &funct)
  {
    BoardPos pos(-1, -1);
    for (pos.m_row = 0; pos.m_row <= BoardPos::BoardPos::SIZE ; ++pos.m_row)
        for (pos.m_col = 0 ; pos.m_col < BoardPos::BoardPos::SIZE ; ++pos.m_col)
          funct(pos);
  }

  template<class F>
  inline void forAll(F const &funct)
  {
    forAllPos([&](BoardPos const &pos)
    {
       funct(getJewel(pos));
    });
  }
  /**
   * @brief randomize assigns random colors so that there are no strikes
   */
  void randomize();

  /**
   * @brief getJewel
   * @param pos
   * @return
   * @throw if trying to get jewel from row 0
   */
  Jewel &getJewel(BoardPos pos);
  Jewel const &getJewel(BoardPos pos) const;

  void kill(BoardPos pos) override;

private:
  BoardCallback& m_callback;
  Jewel m_jewels[BoardPos::SIZE + 1][BoardPos::SIZE];
};

#endif // BOARD_H
