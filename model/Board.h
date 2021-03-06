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
#include <vector>

/**
 * @brief The BoardCallback struct is used by model to inform GUI
 * of model changes
 */
struct BoardCallback
{
  /**
   * @brief kill removes the jewel at the given position
   * @param pos
   */
  virtual void kill(std::vector<BoardPos> const &pos) = 0;
  /**
   * @brief isAlive
   * @param pos
   * @return wether cell at given position is dead (or dying)
   */
  virtual bool isAlive(BoardPos pos) const = 0;

};

class Board //: public BoardCallback
{
public:
  /**
   * @brief Board
   * @param callback
   */
  Board();
  virtual ~Board();

  void setCallback(BoardCallback *callback);
  BoardCallback &getCallback();
  BoardCallback const &getCallback() const;
  /**
   * loops upwards to quickly propagate falling
   * @param alsoFirstRow default different than in JewelBoard
   */
  template<class F>
  inline void forAllPos(F const &funct, bool alsoFirstRow = false)
  {
    BoardPos pos;
    //for (pos.m_row = 1; pos.m_row <= BoardPos::BoardPos::SIZE ; ++pos.m_row)
    for (pos.m_row = BoardPos::BoardPos::NUM_ROWS; pos.m_row >= (alsoFirstRow ? 0 : 1)  ; --pos.m_row)
        for (pos.m_col = 0 ; pos.m_col < BoardPos::BoardPos::NUM_COLS ; ++pos.m_col)
          funct(pos);
  }

  template<class F>
  inline void forAll(F const &funct, bool alsoFirstRow = false)
  {
    forAllPos([&](BoardPos const &pos)
    {
       funct(getJewel(pos), alsoFirstRow);
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
  Jewel &getJewel(BoardPos pos, bool allowFirstRow = false);
  Jewel const &getJewel(BoardPos pos, bool allowFirstRow = false) const;

  //void kill(std::vector<BoardPos> const & killed) override;
  //bool isAlive(BoardPos pos) const override;

  void update();

  void pureSwap(BoardPos pos, BoardPos pos2);
private:
  BoardCallback* m_callback;
  //@todo duplicating jewels here is a bad idea. maybe can be unified is JewelObject inherits from Jewel
  // and JewelObject from Jewel?
  Jewel* m_jewels[BoardPos::NUM_ROWS + 1][BoardPos::NUM_COLS];
};

#endif // BOARD_H
