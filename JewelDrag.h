/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef JEWELDRAG_H
#define JEWELDRAG_H

#include <utils/Vector2D.h>
#include <model/BoardPos.h>
#include <model/JewelSwap.h>


class JewelBoard;
namespace dani {
  class Effect;
}

/**
 * @brief The JewelDrag class mimicks Candy Crush swipe.
 * swap is triggered when finger moves approx half a tile
 * (no need to raise finger)
 */
class JewelDrag
{
public:
  JewelDrag(JewelBoard &board);
  /** Updates board with automatic swipe*/
  void update();
  /** mouse button down*/
  void drag();
  /** mouse button up*/
  void drop();
private:
  JewelBoard &m_board;
  /** Invalid is not dragging*/
  Vector2D m_fromPixel;
  /** redundant wrt m_fromPixel to avoid recalculation*/
  BoardPos m_fromPos;
  BoardPos m_toPos;
  JewelSwap m_modelSwap;
  dani::Effect *m_swapEffect;
//  BoardPos m_selected;

};

#endif // JEWELDRAG_H
