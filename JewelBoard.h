/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef JEWEL_BOARD
#define JEWEL_BOARD

#include <iostream>
#include <utils/ValueEffect.h>
#include "model/BoardPos.h"
#include <model/JewelStrike.h>
#include "GameObject.h"
#include "JewelDrag.h"
#include <functional>
#include <vector>
#include <list>
#include <iosfwd>

class JewelObject;
class Match;
class Board;
struct SDL_MouseButtonEvent;

/**
 * @brief The JewelBoard class renders the jewels in the board
 */
class JewelBoard : public GameObject, public BoardCallback
{
public:
  virtual ~JewelBoard() {}
  JewelBoard(Match &match);

  void draw() override;
  bool update() override;
  void clean() override;
  std::string type() override { return "JewelBoard";}


  void load(std::unique_ptr<LoaderParams> const &pParams) override;

  //BoardCallback
  void kill(std::vector<BoardPos> const & killed) override;
  bool isAlive(BoardPos pos) const override;
  //BoardCallback

  /**
     * @brief getJewel
     * @param row 0 to SIZE
     * @param col
     * @return
     */
  JewelObject& getJewel(BoardPos const pos);
  JewelObject const& getJewel(BoardPos const pos) const;


  template<class F>
  inline void forAllCols(F const &funct)
  {
    for (short col = 0 ; col < BoardPos::BoardPos::NUM_COLS ; ++col)
      funct(col);
  }

  //using template more efficient than std::function
  /**
     * loops upwards to quickly propagate falling
     * @param alsoFirstRow default different than in Board
     */
  template<class F>
  inline void forAllPos(F const &funct, bool alsoFirstRow = true)
  {
    BoardPos pos;
    forAllCols([&](short col)
    {
      pos.m_col = col;
      for (pos.m_row = BoardPos::BoardPos::NUM_ROWS; pos.m_row >= (alsoFirstRow ? 0 : 1)  ; --pos.m_row)
        funct(pos);
    });
  }


  template<class F>
  inline void forAll(F const &funct, bool alsoFirstRow = true)
  {
    forAllPos([&](BoardPos const &pos)
    {
      funct(getJewel(pos));
    }, alsoFirstRow);
  }
  /**
     * @brief getJewelAt
     * @param ev
     * @return not valid board if not withn board
     */
  BoardPos getJewelAt(const Vector2D &pixel) const;
  Vector2D getJewelPixel(BoardPos pos) const;

  Board &getModel();
  Board const &getModel() const;

private:
  /**
   * @brief findJustDeads
   * @param col
   * @return wether something changed
   */
  bool findJustDeads(short col);
  /**
     * @brief scoreAt manages the scoring
     * @param pos
     * @param score
     */
  void scoreAt(const std::vector<BoardPos> &killed, int numJewels);

  /**
     * Just swap the 2 pointers to the Jewels
     */
  void pureSwap(BoardPos pos, BoardPos pos2);
  /** Move jewel to next row
     * @return true if it cannot fall anymore (supposing lower cells have already been updated)
     */
  void shiftDown(BoardPos pos);

  //extra row is for falling new jewels
  //@todo convert again to static array
  typedef std::vector<JewelObject*> Column;
  Column m_jewels[ BoardPos::NUM_COLS];

  void createInitialJewelsBoard();
  Match &m_match;
  /**
     * @brief _offset where board is painted
     */
  Vector2D const m_offset;
  Vector2D const m_size;
  JewelDrag m_drag;
  JewelStrike m_strike;
  bool m_jewelsFalling;
  dani::CompositeEffect m_scoreEffects;
  std::string m_lastDump;
};

std::ostream & operator<<(std::ostream & strm, JewelBoard &board);

#endif /* JEWEL_BOARD */
